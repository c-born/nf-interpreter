# This folder contains all the elements used for .NET nanoFramework dev container

You'll find Docker files for .NET nanoFramework. They are used to facilitate building images.

The available pre build images are:

* ghcr.io/nanoframework/dev-container-all: contains all elements to build any image. **Important**: the size of this container is very large, if you are interested only in building one of the image, you better need to une one of the following dedicated image
* ghcr.io/nanoframework/dev-container-chibios: contains all elements to build any ESP32 image
* ghcr.io/nanoframework/dev-container-ti: contains all elements to build any ESP32 image
* ghcr.io/nanoframework/dev-container-esp32: contains all elements to build any ESP32 image
* ghcr.io/nanoframework/dev-container-azure-rtos: contains all elements to build any Azure RTOS based image
 
To choose the dev container you want to use, adjust `devcontainer.json` and change the `"dockerFile": "Dockerfile"` elements for the image you'd liked to use:

* `Dockerfile.All` to use the pre build container with all the elements to build all the images
* `Dockerfile.AzureRTOS` to use the pre build container with all the elements to build Azure RTOS based devices
* `Dockerfile.ChibiOS` to use the pre build container with all the elements to build ChibiOS based devices
* `Dockerfile.ESP32` to use the pre build container with all the elements to build ESP32 based devices
* `Dockerfile.TI` to use the pre build container with all the elements to build TI based devices
* `./sources/Dockerfile.All` to use build the container from the source with all the elements to build all the images
* `./sources/Dockerfile.AzureRTOS` to use build the container from the source with all the elements to build Azure RTOS based devices
* `./sources/Dockerfile.ChibiOS` to use build the container from the source with all the elements to build ChibiOS based devices
* `./sources/Dockerfile.ESP32` to use build the container from the source with all the elements to build ESP32 based devices
* `./sources/Dockerfile.TI` to use build the container from the source with all the elements to build TI based devices