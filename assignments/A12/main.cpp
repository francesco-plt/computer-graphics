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
public:
    // function to generate a GLFWwindow object
    GLFWwindow *initWindow(const char *wName)
    {
        glfwInit();
        glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        GLFWwindow *window = glfwCreateWindow(WIDTH, HEIGHT, wName, nullptr, nullptr);
        return window;
    }

    void createInstance()
    {
        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = "Hello Triangle";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "No Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_0;
    }

    std::set<std::string> get_supported_extensions()
    {
        uint32_t count;
        vkEnumerateInstanceExtensionProperties(nullptr, &count, nullptr); // get number of extensions
        std::vector<VkExtensionProperties> extensions(count);
        vkEnumerateInstanceExtensionProperties(nullptr, &count, extensions.data()); // populate buffer
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

    int run()
    {
        const char pName[] = "Assignment 12";
        VkInstance instance;
        uint32_t glfwExtensionCount = 0;
        const char **glfwExtensions;

        // creating the window
        window = initWindow(pName);

        // enumerating extensions
        glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
        vkEnumerateInstanceExtensionProperties(nullptr, &glfwExtensionCount, nullptr);
        std::cout << glfwExtensionCount << " extensions supported:\n";
        std::set res = get_supported_extensions();
        for (auto it = res.begin(); it != res.end(); ++it)
            std::cout << *it << '\n';

        // populating instance
        createInstance();

        // main loop

        /*  Recall from slides:
            The minimal main loop just waits for the user to close the window with
            the glfwWindowShouldClose(…) and the glfwPollEvents() commands,
            and then leaves the loop: */
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
        }

        // and releasing the created object
        cleanup();
        return 0;
    }

private:
    VkInstance instance;
    GLFWwindow *window;
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