//
// Copyright 2016 The ANGLE Project Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
//
// RendererVk.h:
//    Defines the class interface for RendererVk.
//

#ifndef LIBANGLE_RENDERER_VULKAN_RENDERERVK_H_
#define LIBANGLE_RENDERER_VULKAN_RENDERERVK_H_

#include <condition_variable>
#include <deque>
#include <memory>
#include <mutex>
#include <queue>
#include <thread>

#include "common/vulkan/vk_ext_provoking_vertex.h"

#include "common/PackedEnums.h"
#include "common/PoolAlloc.h"
#include "common/angleutils.h"
#include "common/vulkan/vk_headers.h"
#include "common/vulkan/vulkan_icd.h"
#include "libANGLE/BlobCache.h"
#include "libANGLE/Caps.h"
#include "libANGLE/renderer/vulkan/CommandProcessor.h"
#include "libANGLE/renderer/vulkan/DebugAnnotatorVk.h"
#include "libANGLE/renderer/vulkan/QueryVk.h"
#include "libANGLE/renderer/vulkan/ResourceVk.h"
#include "libANGLE/renderer/vulkan/UtilsVk.h"
#include "libANGLE/renderer/vulkan/vk_format_utils.h"
#include "libANGLE/renderer/vulkan/vk_helpers.h"
#include "libANGLE/renderer/vulkan/vk_internal_shaders_autogen.h"
#include "libANGLE/renderer/vulkan/vk_mem_alloc_wrapper.h"

namespace egl
{
class Display;
class BlobCache;
}  // namespace egl

namespace rx
{
class DisplayVk;
class FramebufferVk;

namespace vk
{
struct Format;

static constexpr size_t kMaxExtensionNames = 200;
using ExtensionNameList                    = angle::FixedVector<const char *, kMaxExtensionNames>;
}  // namespace vk

// Supports one semaphore from current surface, and one semaphore passed to
// glSignalSemaphoreEXT.
using SignalSemaphoreVector = angle::FixedVector<VkSemaphore, 2>;

inline void CollectGarbage(std::vector<vk::GarbageObject> *garbageOut) {}

template <typename ArgT, typename... ArgsT>
void CollectGarbage(std::vector<vk::GarbageObject> *garbageOut, ArgT object, ArgsT... objectsIn)
{
    if (object->valid())
    {
        garbageOut->emplace_back(vk::GarbageObject::Get(object));
    }
    CollectGarbage(garbageOut, objectsIn...);
}

class RendererVk : angle::NonCopyable
{
  public:
    RendererVk();
    ~RendererVk();

    angle::Result initialize(DisplayVk *displayVk,
                             egl::Display *display,
                             const char *wsiExtension,
                             const char *wsiLayer);
    // Reload volk vk* function ptrs if needed for an already initialized RendererVk
    void reloadVolkIfNeeded() const;
    void onDestroy();

    void notifyDeviceLost();
    bool isDeviceLost() const;
    bool hasSharedGarbage();
    void releaseSharedResources(vk::ResourceUseList *resourceList);

    std::string getVendorString() const;
    std::string getRendererDescription() const;

    gl::Version getMaxSupportedESVersion() const;
    gl::Version getMaxConformantESVersion() const;

    VkInstance getInstance() const { return mInstance; }
    VkPhysicalDevice getPhysicalDevice() const { return mPhysicalDevice; }
    const VkPhysicalDeviceProperties &getPhysicalDeviceProperties() const
    {
        return mPhysicalDeviceProperties;
    }
    const VkPhysicalDeviceSubgroupProperties &getPhysicalDeviceSubgroupProperties() const
    {
        return mSubgroupProperties;
    }
    const VkPhysicalDeviceFeatures &getPhysicalDeviceFeatures() const
    {
        return mPhysicalDeviceFeatures;
    }
    VkDevice getDevice() const { return mDevice; }

    const vk::Allocator &getAllocator() const { return mAllocator; }

    angle::Result selectPresentQueueForSurface(DisplayVk *displayVk,
                                               VkSurfaceKHR surface,
                                               uint32_t *presentQueueOut);

    const gl::Caps &getNativeCaps() const;
    const gl::TextureCapsMap &getNativeTextureCaps() const;
    const gl::Extensions &getNativeExtensions() const;
    const gl::Limitations &getNativeLimitations() const;

    uint32_t getQueueFamilyIndex() const { return mCurrentQueueFamilyIndex; }
    const VkQueueFamilyProperties &getQueueFamilyProperties() const
    {
        return mQueueFamilyProperties[mCurrentQueueFamilyIndex];
    }

    const vk::MemoryProperties &getMemoryProperties() const { return mMemoryProperties; }

    const vk::Format &getFormat(GLenum internalFormat) const
    {
        return mFormatTable[internalFormat];
    }

    const vk::Format &getFormat(angle::FormatID formatID) const { return mFormatTable[formatID]; }

    angle::Result getPipelineCacheSize(DisplayVk *displayVk, size_t *pipelineCacheSizeOut);
    angle::Result syncPipelineCacheVk(DisplayVk *displayVk);

    // Issues a new serial for linked shader modules. Used in the pipeline cache.
    Serial issueShaderSerial();

    const angle::FeaturesVk &getFeatures() const { return mFeatures; }
    uint32_t getMaxVertexAttribDivisor() const { return mMaxVertexAttribDivisor; }
    VkDeviceSize getMaxVertexAttribStride() const { return mMaxVertexAttribStride; }

    VkDeviceSize getMinImportedHostPointerAlignment() const
    {
        return mMinImportedHostPointerAlignment;
    }
    uint32_t getDefaultUniformBufferSize() const { return mDefaultUniformBufferSize; }

    bool isMockICDEnabled() const { return mEnabledICD == angle::vk::ICD::Mock; }

    // Query the format properties for select bits (linearTilingFeatures, optimalTilingFeatures and
    // bufferFeatures).  Looks through mandatory features first, and falls back to querying the
    // device (first time only).
    bool hasLinearImageFormatFeatureBits(VkFormat format,
                                         const VkFormatFeatureFlags featureBits) const;
    VkFormatFeatureFlags getImageFormatFeatureBits(VkFormat format,
                                                   const VkFormatFeatureFlags featureBits) const;
    bool hasImageFormatFeatureBits(VkFormat format, const VkFormatFeatureFlags featureBits) const;
    bool hasBufferFormatFeatureBits(VkFormat format, const VkFormatFeatureFlags featureBits) const;

    ANGLE_INLINE egl::ContextPriority getDriverPriority(egl::ContextPriority priority)
    {
        return mPriorities[priority];
    }

    // Queue submit that originates from the main thread
    angle::Result queueSubmit(vk::Context *context,
                              egl::ContextPriority priority,
                              const VkSubmitInfo &submitInfo,
                              vk::ResourceUseList *resourceList,
                              const vk::Fence *fence,
                              Serial *serialOut);
    angle::Result queueWaitIdle(vk::Context *context, egl::ContextPriority priority);
    angle::Result deviceWaitIdle(vk::Context *context);
    VkResult queuePresent(egl::ContextPriority priority, const VkPresentInfoKHR &presentInfo);

    // This command buffer should be submitted immediately via queueSubmitOneOff.
    angle::Result getCommandBufferOneOff(vk::Context *context,
                                         vk::PrimaryCommandBuffer *commandBufferOut);

    // Fire off a single command buffer immediately with default priority.
    // Command buffer must be allocated with getCommandBufferOneOff and is reclaimed.
    angle::Result queueSubmitOneOff(vk::Context *context,
                                    vk::PrimaryCommandBuffer &&primary,
                                    egl::ContextPriority priority,
                                    const vk::Fence *fence,
                                    Serial *serialOut);

    angle::Result newSharedFence(vk::Context *context, vk::Shared<vk::Fence> *sharedFenceOut);
    inline void resetSharedFence(vk::Shared<vk::Fence> *sharedFenceIn)
    {
        std::lock_guard<std::mutex> lock(mFenceRecyclerMutex);
        sharedFenceIn->resetAndRecycle(&mFenceRecycler);
    }

    angle::Result getNextSubmitFence(vk::Shared<vk::Fence> *sharedFenceOut, bool reset);

    template <typename... ArgsT>
    void collectGarbageAndReinit(vk::SharedResourceUse *use, ArgsT... garbageIn)
    {
        std::vector<vk::GarbageObject> sharedGarbage;
        CollectGarbage(&sharedGarbage, garbageIn...);
        if (!sharedGarbage.empty())
        {
            collectGarbage(std::move(*use), std::move(sharedGarbage));
        }
        else
        {
            // Force releasing "use" even if no garbage was created.
            use->release();
        }
        // Keep "use" valid.
        use->init();
    }

    void collectGarbage(vk::SharedResourceUse &&use, std::vector<vk::GarbageObject> &&sharedGarbage)
    {
        if (!sharedGarbage.empty())
        {
            std::lock_guard<std::mutex> lock(mGarbageMutex);
            mSharedGarbage.emplace_back(std::move(use), std::move(sharedGarbage));
        }
    }

    vk::Shared<vk::Fence> getLastSubmittedFence(const vk::Context *context) const
    {
        return mCommandProcessor.getLastSubmittedFence(context);
    }
    void handleDeviceLost() { mCommandProcessor.handleDeviceLost(); }

    angle::Result getPipelineCache(vk::PipelineCache **pipelineCache);
    void onNewGraphicsPipeline()
    {
        std::lock_guard<std::mutex> lock(mPipelineCacheMutex);
        mPipelineCacheDirty = true;
    }

    void onNewValidationMessage(const std::string &message);
    std::string getAndClearLastValidationMessage(uint32_t *countSinceLastClear);

    uint64_t getMaxFenceWaitTimeNs() const;

    ANGLE_INLINE Serial getCurrentQueueSerial()
    {
        if (getFeatures().commandProcessor.enabled)
        {
            return mCommandProcessor.getCurrentQueueSerial();
        }
        std::lock_guard<std::mutex> lock(mQueueSerialMutex);
        return mCurrentQueueSerial;
    }
    ANGLE_INLINE Serial getLastSubmittedQueueSerial()
    {
        if (getFeatures().commandProcessor.enabled)
        {
            return mCommandProcessor.getLastSubmittedSerial();
        }
        std::lock_guard<std::mutex> lock(mQueueSerialMutex);
        return mLastSubmittedQueueSerial;
    }
    ANGLE_INLINE Serial getLastCompletedQueueSerial()
    {
        std::lock_guard<std::mutex> lock(mQueueSerialMutex);
        return mLastCompletedQueueSerial;
    }

    void onCompletedSerial(Serial serial);

    VkResult getLastPresentResult(VkSwapchainKHR swapchain)
    {
        return mCommandProcessor.getLastPresentResult(swapchain);
    }

    bool enableDebugUtils() const { return mEnableDebugUtils; }

    SamplerCache &getSamplerCache() { return mSamplerCache; }
    SamplerYcbcrConversionCache &getYuvConversionCache() { return mYuvConversionCache; }
    vk::ActiveHandleCounter &getActiveHandleCounts() { return mActiveHandleCounts; }

    // Queue commands to worker thread for processing
    void queueCommand(vk::Context *context, vk::CommandProcessorTask *command)
    {
        mCommandProcessor.queueCommand(context, command);
    }
    bool hasPendingError() const { return mCommandProcessor.hasPendingError(); }
    vk::Error getAndClearPendingError() { return mCommandProcessor.getAndClearPendingError(); }
    void waitForCommandProcessorIdle(vk::Context *context)
    {
        ASSERT(getFeatures().asynchronousCommandProcessing.enabled);
        mCommandProcessor.waitForWorkComplete(context);
    }

    void finishToSerial(vk::Context *context, Serial serial)
    {
        mCommandProcessor.finishToSerial(context, serial);
    }

    void checkCompletedCommands(vk::Context *context)
    {
        mCommandProcessor.checkCompletedCommands(context);
    }

    void finishAllWork(vk::Context *context) { mCommandProcessor.finishAllWork(context); }
    VkQueue getVkQueue(egl::ContextPriority priority) const { return mQueues[priority]; }

    bool getEnableValidationLayers() const { return mEnableValidationLayers; }

    vk::ResourceSerialFactory &getResourceSerialFactory() { return mResourceSerialFactory; }

    void setGlobalDebugAnnotator();

    void outputVmaStatString();

    angle::Result cleanupGarbage(bool block);

  private:
    angle::Result initializeDevice(DisplayVk *displayVk, uint32_t queueFamilyIndex);
    void ensureCapsInitialized() const;

    void queryDeviceExtensionFeatures(const vk::ExtensionNameList &deviceExtensionNames);

    void initFeatures(DisplayVk *display, const vk::ExtensionNameList &extensions);
    void initPipelineCacheVkKey();
    angle::Result initPipelineCache(DisplayVk *display,
                                    vk::PipelineCache *pipelineCache,
                                    bool *success);

    template <VkFormatFeatureFlags VkFormatProperties::*features>
    VkFormatFeatureFlags getFormatFeatureBits(VkFormat format,
                                              const VkFormatFeatureFlags featureBits) const;

    template <VkFormatFeatureFlags VkFormatProperties::*features>
    bool hasFormatFeatureBits(VkFormat format, const VkFormatFeatureFlags featureBits) const;

    egl::Display *mDisplay;

    mutable bool mCapsInitialized;
    mutable gl::Caps mNativeCaps;
    mutable gl::TextureCapsMap mNativeTextureCaps;
    mutable gl::Extensions mNativeExtensions;
    mutable gl::Limitations mNativeLimitations;
    mutable angle::FeaturesVk mFeatures;

    VkInstance mInstance;
    bool mEnableValidationLayers;
    bool mEnableDebugUtils;
    angle::vk::ICD mEnabledICD;
    VkDebugUtilsMessengerEXT mDebugUtilsMessenger;
    VkDebugReportCallbackEXT mDebugReportCallback;
    VkPhysicalDevice mPhysicalDevice;
    VkPhysicalDeviceProperties mPhysicalDeviceProperties;
    VkPhysicalDeviceFeatures mPhysicalDeviceFeatures;
    VkPhysicalDeviceLineRasterizationFeaturesEXT mLineRasterizationFeatures;
    VkPhysicalDeviceProvokingVertexFeaturesEXT mProvokingVertexFeatures;
    VkPhysicalDeviceVertexAttributeDivisorFeaturesEXT mVertexAttributeDivisorFeatures;
    VkPhysicalDeviceVertexAttributeDivisorPropertiesEXT mVertexAttributeDivisorProperties;
    VkPhysicalDeviceTransformFeedbackFeaturesEXT mTransformFeedbackFeatures;
    VkPhysicalDeviceIndexTypeUint8FeaturesEXT mIndexTypeUint8Features;
    VkPhysicalDeviceSubgroupProperties mSubgroupProperties;
    VkPhysicalDeviceExternalMemoryHostPropertiesEXT mExternalMemoryHostProperties;
    VkPhysicalDeviceShaderFloat16Int8FeaturesKHR mShaderFloat16Int8Features;
    VkPhysicalDeviceShaderAtomicFloatFeaturesEXT mShaderAtomicFloatFeature;
    VkPhysicalDeviceDepthStencilResolvePropertiesKHR mDepthStencilResolveProperties;
    VkExternalFenceProperties mExternalFenceProperties;
    VkExternalSemaphoreProperties mExternalSemaphoreProperties;
    VkPhysicalDeviceSamplerYcbcrConversionFeatures mSamplerYcbcrConversionFeatures;
    std::vector<VkQueueFamilyProperties> mQueueFamilyProperties;
    std::mutex mQueueMutex;
    angle::PackedEnumMap<egl::ContextPriority, VkQueue> mQueues;
    angle::PackedEnumMap<egl::ContextPriority, egl::ContextPriority> mPriorities;
    uint32_t mCurrentQueueFamilyIndex;
    uint32_t mMaxVertexAttribDivisor;
    VkDeviceSize mMaxVertexAttribStride;
    VkDeviceSize mMinImportedHostPointerAlignment;
    uint32_t mDefaultUniformBufferSize;
    VkDevice mDevice;
    AtomicSerialFactory mQueueSerialFactory;
    AtomicSerialFactory mShaderSerialFactory;

    std::mutex mQueueSerialMutex;
    Serial mLastCompletedQueueSerial;
    Serial mLastSubmittedQueueSerial;
    Serial mCurrentQueueSerial;

    bool mDeviceLost;

    std::mutex mFenceRecyclerMutex;
    vk::Recycler<vk::Fence> mFenceRecycler;

    std::mutex mGarbageMutex;
    vk::SharedGarbageList mSharedGarbage;

    vk::MemoryProperties mMemoryProperties;
    vk::FormatTable mFormatTable;

    // All access to the pipeline cache is done through EGL objects so it is thread safe to not use
    // a lock.
    std::mutex mPipelineCacheMutex;
    vk::PipelineCache mPipelineCache;
    egl::BlobCache::Key mPipelineCacheVkBlobKey;
    uint32_t mPipelineCacheVkUpdateTimeout;
    bool mPipelineCacheDirty;
    bool mPipelineCacheInitialized;

    // A cache of VkFormatProperties as queried from the device over time.
    mutable std::array<VkFormatProperties, vk::kNumVkFormats> mFormatProperties;

    // Latest validation data for debug overlay.
    std::string mLastValidationMessage;
    uint32_t mValidationMessageCount;

    DebugAnnotatorVk mAnnotator;

    // How close to VkPhysicalDeviceLimits::maxMemoryAllocationCount we allow ourselves to get
    static constexpr double kPercentMaxMemoryAllocationCount = 0.3;
    // How many objects to garbage collect before issuing a flush()
    uint32_t mGarbageCollectionFlushThreshold;

    // Only used for "one off" command buffers.
    vk::CommandPool mOneOffCommandPool;

    struct PendingOneOffCommands
    {
        Serial serial;
        vk::PrimaryCommandBuffer commandBuffer;
    };
    std::deque<PendingOneOffCommands> mPendingOneOffCommands;

    // Command Processor Thread
    vk::CommandProcessor mCommandProcessor;
    std::thread mCommandProcessorThread;
    // mNextSubmitFence is the fence that's going to be signaled at the next submission.  This is
    // used to support SyncVk objects, which may outlive the context (as EGLSync objects).
    vk::Shared<vk::Fence> mNextSubmitFence;
    std::mutex mNextSubmitFenceMutex;

    // track whether we initialized (or released) glslang
    bool mGlslangInitialized;

    vk::Allocator mAllocator;
    SamplerCache mSamplerCache;
    SamplerYcbcrConversionCache mYuvConversionCache;
    vk::ActiveHandleCounter mActiveHandleCounts;

    // Tracks resource serials.
    vk::ResourceSerialFactory mResourceSerialFactory;
};

}  // namespace rx

#endif  // LIBANGLE_RENDERER_VULKAN_RENDERERVK_H_