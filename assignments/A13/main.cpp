// Following the Vulkan Tutorial as shown in the enclose Assignment13.pdf, complete
// this Vulkan initialization sample. You can copy and past code from Example E08,
// or from other assginments such as Assignment0.cpp

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include <vector>

const uint32_t WIDTH = 640;
const uint32_t HEIGHT = 480;

class Assignment13
{
private:
    static constexpr char pName[] = "Assignment 12";
    VkInstance instance;
    GLFWwindow *window;
    uint32_t glfwExtensionCount;
    const char **glfwExtensions;
    VkApplicationInfo appInfo{};
    VkInstanceCreateInfo createInfo{};

public:
    void run()
    {
        initWindow();
        initVulkan();
        initApp();
        mainLoop();
        cleanup();
    }

    GLFWwindow *initWindow(const char *wName)
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, wName, nullptr, nullptr);
        return window;
    }

    void initVulkan()
    {
        createInstance();
        // Continue with:
        // Prsentation Surface Creation
        // Physical Device selection
        // Logical Device creation
        // Command Pool creation
        // Command Buffer creation
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
        VkInstanceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        createInfo.pApplicationInfo = &appInfo;
        createInfo.enabledExtensionCount = glfwExtensionCount;
        createInfo.ppEnabledExtensionNames = glfwExtensions;
        createInfo.enabledLayerCount = 0;

        VkResult result = vkCreateInstance(&createInfo, nullptr, &instance);

        if (result != VK_SUCCESS)
        {
            throw std::runtime_error("failed to create instance!");
        }
    }

    void initApp()
    {
        // This will not be needed in this assignment!
    }

    void mainLoop()
    {
        // Wait for the window to close [you can take it from Assingment 12]
    }

    void cleanup()
    {
        vkDestroySurfaceKHR(instance, surface, nullptr); // new code
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