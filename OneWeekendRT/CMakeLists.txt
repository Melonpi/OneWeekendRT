INCLUDE_DIRECTORIES(./include)

SET(HEADER_FILES 
	./include/Camera.h
    ./include/Types.h
    ./include/Vec3.h
    ./include/Hitable.h
	./include/HitableList.h
	./include/Material.h
    ./include/Misc.h
    ./include/Ray.h
	./include/RNG.h
    ./include/Sphere.h
    ./include/stb_image.h
    ./include/stb_image_resize.h
    ./include/stb_image_write.h
    )

SET(SRC_FILES 
    ./src/main.cpp
    ./src/stb_image_write.cpp
	./src/HitableList.cpp
	./src/Sphere.cpp
	./src/RNG.cpp
    )

SOURCE_GROUP("Header Files" FILES ${HEADER_FILES})
SOURCE_GROUP("SRC FILES" FILES ${SRC_FILES})

ADD_EXECUTABLE(OneWeekendRT ${SRC_FILES} ${HEADER_FILES})

INSTALL(TARGETS OneWeekendRT DESTINATION ${PROJECT_BINARY_DIR})