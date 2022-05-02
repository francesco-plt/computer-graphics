// Following the Vulkan Tutorial until the
// Drawing a triangle -> Setup -> Instance
// section (currently at https://vulkan-tutorial.com/Drawing_a_triangle/Setup/Instance)
// create a 640 x 480 window, with title "Assignment 12", and list the global
// extensions supported by your O.S.

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <set>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <cstring>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

// vulkan window hello world
class Assignment12
{
private:
    static constexpr char pName[] = "Assignment 12";
    VkInstance instance;
    VkResult result;
    GLFWwindow *window;
    uint32_t glfwExtensionCount;
    const char **glfwExtensions;
    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo createInfo{};

public:
    int run()
    {
        // creating the window
        window = initWindow();

        // populating instance
        createInstance();

        // getting info about supported extensions
        std::set res = get_supported_extensions();
        std::cout << res.size() << " extensions supported:" << std::endl;
        for (auto it = res.begin(); it != res.end(); ++it)
            std::cout << *it << '\n';

        // main loop
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }

        // releasing the created object
        cleanup();

        return 0;
    }

    // function to generate a GLFWwindow object
    GLFWwindow *initWindow()
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, pName, nullptr, nullptr);
        return window;
    }

    void createInstance()
    {
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
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

    std::set<std::string> get_supported_extensions()
    {
        vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, nullptr); // get number of extensions
        std::vector<VkExtensionProperties> extensions(glfwExtensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, extensions.data()); // populate buffer
        std::set<std::string> results;
        for (auto &extension : extensions)
        {
            results.insert(extension.extensionName);
        }
        return results;
    }

    void cleanup()
    {
        vkDestroyInstance(instance, nullptr);
        glfwDestroyWindow(window);
        glfwTerminate();
    }
};

int main()
{
    Assignment12 app;
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