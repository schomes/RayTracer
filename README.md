# RayTracer 

This program implements ray tracing to create computer generated images. Spheres and triangle meshes are supported. Simple linear algebra classes are also implemented.

![Alt text](/samples/still_life-1.png?raw=true "Still Life Image")

## Features 

This ray tracer supports the following: 

1. Phong reflection model
2. Point lights/directional lights  
3. Hard shadows/soft shadows 
4. Textures 
5. Smooth shading 
6. Perspective/parallel projections 
7. Reflection
8. Refraction, transparent surfaces
9. Depth of field

### Sample images

![Alt text](/samples/vase-1.png?raw=true "Vase")

![Alt text](/samples/monkey_lava-1.png?raw=true "Monkey and lava sphere")
![Alt text](/samples/blur-1.png?raw=true "Depth of field")
![Alt text](/samples/soft_shadows-1.png?raw=true "Soft shadows")
![Alt text](/samples/spheres-1.png?raw=true "Spheres")
![Alt text](/samples/spheres-2.png?raw=true "Spheres")
![Alt text](/samples/earth-1.png?raw=true "Earth")


## What can be improved
### Render Time
Currently, it takes a long time to produce a small, simple image. We can improve the rendering time by adopting a multithreaded approach. OpenMP is an API that can be used for multithreaded programming. 

### Code Organization 
To support more features in the future, it is important to improve the structure of the program. Similar data regarding rays gets passed around the program many times. Therefore, a data structure such as a RayPayload could improve readability and scalability by keeping track of rays, the objects they've intersected, and other relevant data. 

Also, it may be more appropriate to move functions in the Kernel class to their own classes. The Kernel class holds a lot of the ray tracing routines; this will not scale well in the future. 
