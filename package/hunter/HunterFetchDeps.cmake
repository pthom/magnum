hunter_add_package(corrade)
if(WITH_GLFWAPPLICATION)
    hunter_add_package(glfw)
endif()
if(WITH_SDL2APPLICATION)
    hunter_add_package(SDL2)
endif()