// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <cstring>
#include <set>
#include <map>
#include <optional>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

struct QueueFamilyIndices
{
    /*
        std::optional is a wrapper that contains no
        value until you assign something to it. At
        any point you can query if it contains a value
        or not by calling its has_value() member function.
    */
    std::optional<uint32_t> graphicsFamily;
    std::optional<uint32_t> presentFamily;

    bool isComplete()
    {
        return graphicsFamily.has_value() && presentFamily.has_value();
    }
};

// vulkan window hello world
class Assignment13
{
private:
    static constexpr char pName[] = "Assignment 13";
    GLFWwindow *window;
    VkInstance instance;
    VkResult result;
    VkSurfaceKHR surface;
    VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
    VkDevice device;
    VkQueue graphicsQueue;
    VkQueue presentQueue;
    VkCommandPool commandPool;
    VkCommandBuffer commandBuffer;

public:
    void run()
    {
        initWindow();
        initVulkan();
        mainLoop();
        cleanup();
    }

    // function to generate a GLFWwindow object
    void initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        window = glfwCreateWindow(WIDTH, HEIGHT, pName, nullptr, nullptr);
    }

    void createInstance()
    {
        VkApplicationInfo appInfo{};
        VkInstanceCreateInfo createInfo{};
        uint32_t glfwExtensionCount;
        const char **glfwExtensions;

        // appinfo
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = pName;
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;

        // createinfo
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        // for now we do not care about layers
        // createInfo.enabledLayerCount = 0;
        // ... all following layer related code is missing

        result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

    void createSurface()
    {
        if (glfwCreateWindowSurface(instance, window, nullptr, &surface) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create window surface!");
        }
    }

    bool isDeviceSuitable(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices = findQueueFamilies(device);
        return indices.isComplete();
    }

    void pickPhysicalDevice()
    {

        // Enumerate devices
        uint32_t deviceCount = 0;
        result = vkEnumeratePhysicalDevices(instance, &deviceCount, nullptr);
        if (result != VK_SUCCESS || deviceCount <= 0)
        {
            throw std::runtime_error("failed to find GPUs with Vulkan Support!");
        }
        std::cout << deviceCount << " Physical Device(s) found \n\n";

        // now we'll put them in a vector and choose the best one
        std::vector<VkPhysicalDevice> devices(deviceCount);
        vkEnumeratePhysicalDevices(instance, &deviceCount, devices.data());

        for (const auto &device : devices)
        {
            if (isDeviceSuitable(device))
            {
                physicalDevice = device;
                std::cout << "Suitable Physical Device Found ("
                          << device << ")\n\n";
                break;
            }
        }

        if (physicalDevice == VK_NULL_HANDLE)
        {
            throw std::runtime_error("failed to find a suitable GPU!");
        }
    }

    void getDeviceInfo()
    {
        // check device properties and features
        // Show device properties
        VkPhysicalDeviceProperties deviceProperties;
        vkGetPhysicalDeviceProperties(physicalDevice, &deviceProperties);

        std::cout << "\tAPI version: 0x" << std::hex << deviceProperties.apiVersion << "\n";
        std::cout << "\tDriver version: 0x" << std::hex << deviceProperties.driverVersion << "\n";
        std::cout << "\tVendor ID: 0x" << std::hex << deviceProperties.vendorID << "\n";
        std::cout << "\tDevice ID: 0x" << std::hex << deviceProperties.deviceID << "\n";
        std::cout << "\tPhysical Device Type: " << deviceProperties.deviceType << "\t";
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
            std::cout << " (Discrete GPU)\n";
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU)
            std::cout << " (Integrated GPU)\n";
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU)
            std::cout << " (Virtual GPU)\n";
        if (deviceProperties.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
            std::cout << " (CPU)\n";
        std::cout << "\tDevice Name: " << deviceProperties.deviceName << "\n";

        // Show device features
        VkPhysicalDeviceFeatures deviceFeatures;
        vkGetPhysicalDeviceFeatures(physicalDevice, &deviceFeatures);

        std::cout << "\n\tPhysical Device Features:\n";
        std::cout << "\t\tgeometryShader = " << deviceFeatures.geometryShader << "\n";
        std::cout << "\t\ttessellationShader = " << deviceFeatures.tessellationShader << "\n";
        std::cout << "\t\tmultiDrawIndirect = " << deviceFeatures.multiDrawIndirect << "\n";
        std::cout << "\t\twideLines = " << deviceFeatures.wideLines << "\n";
        std::cout << "\t\tlargePoints = " << deviceFeatures.largePoints << "\n";
        std::cout << "\t\tmultiViewport = " << deviceFeatures.multiViewport << "\n";
        std::cout << "\t\tocclusionQueryPrecise = " << deviceFeatures.occlusionQueryPrecise << "\n";
        std::cout << "\t\tpipelineStatisticsQuery = " << deviceFeatures.pipelineStatisticsQuery << "\n";
        std::cout << "\t\tshaderFloat64 = " << deviceFeatures.shaderFloat64 << "\n";
        std::cout << "\t\tshaderInt64 = " << deviceFeatures.shaderInt64 << "\n";
        std::cout << "\t\tshaderInt16 = " << deviceFeatures.shaderInt16 << "\n";

        // Show device memory properties
        VkPhysicalDeviceMemoryProperties vpdmp;
        vkGetPhysicalDeviceMemoryProperties(physicalDevice, &vpdmp);

        std::cout << "\n\tMemory Types: " << vpdmp.memoryTypeCount << "\n";
        for (unsigned int i = 0; i < vpdmp.memoryTypeCount; i++)
        {
            VkMemoryType vmt = vpdmp.memoryTypes[i];
            std::cout << "\t\tMemory: " << i << ":";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT) != 0)
                std::cout << " DeviceLocal";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) != 0)
                std::cout << " HostVisible";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_COHERENT_BIT) != 0)
                std::cout << " HostCoherent";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_HOST_CACHED_BIT) != 0)
                std::cout << " HostCached";
            if ((vmt.propertyFlags & VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT) != 0)
                std::cout << " LazilyAllocated";
            std::cout << "\n";
        }

        std::cout << "\n";
    }

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device)
    {
        QueueFamilyIndices indices;
        VkBool32 presentSupport;

        // what follows is the logic to find queue
        // familiy indices to populate struct with

        // we get those queues
        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        // we filter out the ones which supports the graphics bit
        int i = 0;
        for (const auto &queueFamily : queueFamilies)
        {
            presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, surface, &presentSupport);

            if (presentSupport)
            {
                indices.presentFamily = i;
            }

            if ((queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT))
            {
                indices.graphicsFamily = i;
            }

            if (indices.isComplete())
            {
                break;
            }

            i++;
        }

        return indices;
    }

    void createLogicalDevice()
    {
        // Specifying the queues to be created
        QueueFamilyIndices indices = findQueueFamilies(physicalDevice);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = {indices.graphicsFamily.value(), indices.presentFamily.value()};

        /*
            Vulkan lets you assign priorities to queues to influence
            the scheduling of command buffer execution using floating
            point numbers between 0.0 and 1.0. This is required even
            if there is only a single queue:
        */
        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = queueFamily;
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        // Specifying used device features
        VkPhysicalDeviceFeatures deviceFeatures{};

        // Creating the logical device
        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();
        createInfo.pEnabledFeatures = &deviceFeatures;

        // skip validation layers

        // That's it, we're now ready to instantiate the logical device with a call to
        // the appropriately named vkCreateDevice function.
        if (vkCreateDevice(physicalDevice, &createInfo, nullptr, &device) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create logical device!");
        }
        std::cout << "Logical Device Created (" << device << ")\n\n";

        vkGetDeviceQueue(device, indices.graphicsFamily.value(), 0, &graphicsQueue);
        vkGetDeviceQueue(device, indices.presentFamily.value(), 0, &presentQueue);
    }

    void createCommandPool()
    {
        QueueFamilyIndices queueFamilyIndices = findQueueFamilies(physicalDevice);

        VkCommandPoolCreateInfo poolInfo{};
        poolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
        poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
        poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

        if (vkCreateCommandPool(device, &poolInfo, nullptr, &commandPool) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create command pool!");
        }
        std::cout << "Command Pool Created (" << commandPool << ")\n\n";
    }

    void createCommandBuffer()
    {
        VkCommandBufferAllocateInfo allocInfo{};
        allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
        allocInfo.commandPool = commandPool;
        allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        allocInfo.commandBufferCount = 1;

        if (vkAllocateCommandBuffers(device, &allocInfo, &commandBuffer) != VK_SUCCESS)
        {
            throw std::runtime_error("failed to allocate command buffers!");
        }
        std::cout << "Command Buffer Created (" << commandBuffer << ")\n\n";
    }

    /*
    the main part of this assignment is the initVulkan function
    It's articulated in the following steps:
    1. create the instance
    2. create the surface
    3. enumerate and pick the physical device
    4. create the logical device
    5. create the graphic and presentation queues
    6. create a command pool for the graphics queue
    7. create a command buffer for the graphics queue
*/
    void initVulkan()
    {
        createInstance();
        createSurface();
        pickPhysicalDevice();
        getDeviceInfo();
        createLogicalDevice();
        createCommandPool();
        createCommandBuffer();
    }

    void mainLoop()
    {
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }
    }

    void cleanup()
    {
        // vkDestroySurfaceKHR(instance, surface, nullptr);
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main()
{
    Assignment13 app;
    try
    {
        app.run();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}