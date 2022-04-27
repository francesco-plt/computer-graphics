# Vulkan notes

## Swap chains

### Screen synchonization

The CPU, the GPU and the screen visualization run at different and independent speeds. We need an efficient way to sync those elements and avoid **tearing**, which is the phenomenon which presents graphical artifacts on the screen. Tearing manifests itself when the graphic adapter reads the video memory but the application has not finished yet composing the image.

Every graphic adapter sends an interrupt to the processor called **Vsync** whenever it finishes tracing the screen. The application can intercept this interrupt, and start updating the background only when the Vsync signal is received. This is important because if the application starts updating the background but the screen has not yet finished drawing, then tearing happens. 

### Swap chains in Vulkan

In Vulkan, screen synchronization is handled with a generic circular queue, called the **swap chain**. A swap chain is essentially a queue of images that are waiting to be presented to the screen. Our application will acquire such an image to draw to it, and then return it to the queue. How exactly the queue works and the conditions for presenting an image from the queue depend on how the swap chain is set up, but the general purpose of the swap chain is to synchronize the presentation of images with the refresh rate of the screen.