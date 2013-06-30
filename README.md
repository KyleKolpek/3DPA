# 3DPA - 3D Programmer Art

3DPA comes from the idea that 3D assets are difficult to come by, and near
impossible to create by programmers. 2D assets are much easier to create,
allowing programmers to create simple assets in a very short time using readily
available tools (such as MS Paint). Having this convenience allows programmers
to develop 2D games without worrying investing in artwork until the code base is
mature. 3D games are incredibly difficult to develop as a hobbyist or as an
independant company because of the difficutly of obtaining basic assets. The
goal of 3DPA is to provide a convenient, free, cross-platform, open-source,
tool for developing simplistic, but functional, 3D models.

## Design Choices

Due to the difficulty of manipulating traditional models, 3DPA will be voxel
based. This is to say, every model will be made up as a series of cubes. This
allows for "voxel art", the 3D equivelant of pixel art.

The models will be able to be exported as either a proprietary "raw" voxel
format (.3dpa) or as traditional collada models (.dae). Collada is a verbose and
common standard, making it an obvious choice for storing mesh models. The raw
format allows for a smaller file footprint, and lends itself to a being used in
a geometry shader. *Due to optimizations of meshes collada files cannot be
imported, so make sure to save raw formats as well*

## Objectives

* Create an OpenGL context capable of displaying cubes.
* Enable the user to navigate 3D space.
* Enable the user to add and delete cubes.
* Enable the user to choose colors for cubes.
* Decide on an OpenGL text/menu library.
* Add a menu system.
* Define a standard for the raw data files.
* Write an exporter for the raw data files.
* Write an importer for the raw data files.
* Write an exporter for collada files.
* Enable the user to manage groups of cubes that can be modified independently.
* Enable the user to create animations.

## References

* (Collada importer overview)[http://www.wazim.com/Collada_Tutorial_1.htm]
* (Inverse Kinematics)[http://www.darwin3d.com/gdm1998.htm]
