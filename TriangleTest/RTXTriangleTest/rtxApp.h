#pragma once

#include "vulkanapp.h"

struct RTAccelerationStructure {
    VkDeviceMemory                memory;
    VkAccelerationStructureInfoNV accelerationStructureInfo;
    VkAccelerationStructureNV     accelerationStructure;
    uint64_t                      handle;
};

struct RTScene {
    Array<RTAccelerationStructure>  bottomLevelAS;
    RTAccelerationStructure         topLevelAS;
};

class SBTHelper {
public:
    SBTHelper();
    ~SBTHelper() = default;

    void        Initialize(const uint32_t numHitGroups, const uint32_t numMissGroups, const uint32_t shaderHeaderSize);
    void        Destroy();
    void        SetRaygenStage(const VkPipelineShaderStageCreateInfo& stage);
    void        AddStageToHitGroup(const Array<VkPipelineShaderStageCreateInfo>& stages, const uint32_t groupIndex);
    void        AddStageToMissGroup(const VkPipelineShaderStageCreateInfo& stage, const uint32_t groupIndex);

    uint32_t    GetGroupsStride() const;
    uint32_t    GetNumGroups() const;
    uint32_t    GetRaygenOffset() const;
    uint32_t    GetHitGroupsOffset() const;
    uint32_t    GetMissGroupsOffset() const;

    uint32_t                                   GetNumStages() const;
    const VkPipelineShaderStageCreateInfo* GetStages() const;
    const VkRayTracingShaderGroupCreateInfoNV* GetGroups() const;

    uint32_t    GetSBTSize() const;
    bool        CreateSBT(VkDevice device, VkPipeline rtPipeline);
    VkBuffer    GetSBTBuffer() const;

private:
    uint32_t                                   mShaderHeaderSize;
    uint32_t                                   mNumHitGroups;
    uint32_t                                   mNumMissGroups;
    Array<uint32_t>                            mNumHitShaders;
    Array<uint32_t>                            mNumMissShaders;
    Array<VkPipelineShaderStageCreateInfo>     mStages;
    Array<VkRayTracingShaderGroupCreateInfoNV> mGroups;
    vulkanhelpers::Buffer                      mSBT;
};


class RtxApp : public VulkanApp {
public:
    RtxApp();
    ~RtxApp();

protected:
    virtual void InitSettings() override;
    virtual void InitApp() override;
    virtual void FreeResources() override;
    virtual void FillCommandBuffer(VkCommandBuffer commandBuffer, const size_t imageIndex) override;

private:
    bool CreateAS(const VkAccelerationStructureTypeNV type,
        const uint32_t geometryCount,
        const VkGeometryNV* geometries,
        const uint32_t instanceCount,
        RTAccelerationStructure& _as);
    void CreateScene();
    void CreateRaytracingPipeline();
    void CreateDescriptorSet();

private:
    VkDescriptorSetLayout   mRTDescriptorSetLayout;
    VkPipelineLayout        mRTPipelineLayout;
    VkPipeline              mRTPipeline;
    VkDescriptorPool        mRTDescriptorPool;
    VkDescriptorSet         mRTDescriptorSet;

    vulkanhelpers::Buffer   mShaderBindingTable;

    SBTHelper               mSBT;

    RTScene                 mScene;
};

class rtxApp
{
};
