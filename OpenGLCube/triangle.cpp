/*
#include<GL/glut.h>
#include<GL/GL.h>
#include<GL/glxew.h>
int main()
{
	float vertices[] = {
		-0.5f,-0.5f,0.0f,
		0.5f,-0.5f,0.0f,
		0.0f,0.5f,0.0f
	};

	unsigned int VBO;
	glGenBuffers(1, &VBO);//生成唯一ID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//指定为定点缓存对象
	//将顶点数据复制到VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//创建顶点着色器对象
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//创建片元着色器对象
	unsigned int fragmengtShader;
	fragmengtShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmengtShader,1,&fragmengtShaderSource,NULL);
	glCompileShader(fragmengtShader);
	//链接着色器
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmengtShader);
	glLinkProgram(shaderProgram);
	//使用着色器对象
	glUseProgram(shaderProgram);
	//清理着色器
	glDeleteShader(vertexShader);
	glDeleteShader(fragmengtShader);
	//指明顶点格式
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);//0表示顶点数组的起始索引
	//生成VAO并绑定
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}
*/