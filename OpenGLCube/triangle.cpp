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
	glGenBuffers(1, &VBO);//����ΨһID
	glBindBuffer(GL_ARRAY_BUFFER, VBO);//ָ��Ϊ���㻺�����
	//���������ݸ��Ƶ�VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	//����������ɫ������
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	//����ƬԪ��ɫ������
	unsigned int fragmengtShader;
	fragmengtShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmengtShader,1,&fragmengtShaderSource,NULL);
	glCompileShader(fragmengtShader);
	//������ɫ��
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmengtShader);
	glLinkProgram(shaderProgram);
	//ʹ����ɫ������
	glUseProgram(shaderProgram);
	//������ɫ��
	glDeleteShader(vertexShader);
	glDeleteShader(fragmengtShader);
	//ָ�������ʽ
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glDrawArrays(GL_TRIANGLES, 0, 3);//0��ʾ�����������ʼ����
	//����VAO����
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
}
*/