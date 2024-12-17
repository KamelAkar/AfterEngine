#include <condition_variable>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <mutex>


#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glfw3.lib")

constexpr unsigned int scr_width = 800;
constexpr unsigned int scr_height = 600;



void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    {
        
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}



int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(scr_width, scr_height, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << '\n';
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << '\n';
        return -1;
    }

    

    std::cout << "Toutes les taches sont terminees.\n";

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);
        //create a warning purpose

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

/*mutex
#include <functional>
#include <thread>
#include <mutex>
#include <iostream>
#include <queue>
#include <vector>

std::mutex              consoleMutex;

std::condition_variable pingCv;
std::mutex              pingMutex;
std::queue<std::function<void()>> task_queue;

void ThreadFunc(std::stop_token st, int i)
{
    while (!st.stop_requested())
    {
        std::function<void()> task;

        {
            std::unique_lock lock(pingMutex);
            pingCv.wait(lock, [] { return !task_queue.empty();});
            if (task_queue.empty())
                continue;

            task = std::move(task_queue.front());
            task_queue.pop();
        }

        task();

        {
            std::scoped_lock lock(consoleMutex);
            std::cout << "Worker " << i << " - Task ended." << "\n";
        }
    }
}


std::vector<std::jthread> threads;

void add_task(const std::function<void()>& task) {
    {
        std::scoped_lock lock(consoleMutex);
        task_queue.push(task);
    }
    pingCv.notify_one();
}

int main()
{
    for (unsigned int i = 0; i < std::thread::hardware_concurrency(); ++i)
        threads.emplace_back(ThreadFunc, i);

    for (int i = 0; i < 20; ++i)
    {
        add_task([i]
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            {
                std::scoped_lock lock(consoleMutex);
                std::cout << "Task " << i << " completed" << "\n";
            }
        });
    }


    for (auto& t : threads)
        t.request_stop();
        

    pingCv.notify_all();
    return 0;
}
 */

