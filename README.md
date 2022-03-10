# fantasyRender

fantasyRender是一个跨平台的软光栅化渲染器。

实现中只用到了系统调用和c++标准库，不依赖任何第三方库。

目前支持Windows和Linux两个系统下运行。
   
.   
.  
.   
  
使用方式：

1、添加obj模型文件和tga纹理图片文件到models目录下，修改main函数中的文件路径来读取模型文件和纹理图片。

   修改shader.cpp文件来定制自己的vertex shader和fragment shader程序。
   
   （这一步可以省略，已经提供了默认的模型文件和纹理图片，以及默认的blinn phong shader程序）
   
2、通过cmake文件进行编译

3、将编译生成的可执行文件放在build文件夹下

4、运行可执行文件
