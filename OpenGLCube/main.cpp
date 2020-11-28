
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

#define BMP_Header_Length 54  //ͼ���������ڴ���е�ƫ����
GLint texture;//����ID


double x, y, z;

GLfloat vertices[][3] = { {-0.5,-0.5,-0.5},{0.5,-0.5,-0.5},
{0.5,0.5,-0.5}, {-0.5,0.5,-0.5}, {-0.5,-0.5,0.5},
{0.5,-0.5,0.5}, {0.5,0.5,0.5}, {-0.5,0.5,0.5} };


GLfloat colors[][3] = { {1.0,0.0,0.0},{0.0,1.0,0.0},
{0.0,0.0,1.0}, {1.0,1.0,0.0}, {1.0,0.0,1.0},
{0.0,1.0,1.0}, {1.0,1.0,1.0}, {0.0,0.0,0.0} };

/*
GLubyte cubeIndices[24] = { 0,3,2,1,2,3,7,6,0,4,7,3,1,2,6,5,4,5,6,7,0,1,5,4 };

void ColorCube(void)
{
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertices);
	glColorPointer(3, GL_FLOAT, 0, colors);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
}*/

float theta[] = {
	0,0,0
};

float scaleFactor[] = {
	1,1,1
};

float translateDelta[] = {
	0,0,0
};

int axis;



// ����power_of_two�����ж�һ�������ǲ���2����������
int power_of_two(int n)
{
	if (n <= 0)
		return 0;
	return (n & (n - 1)) == 0;
}

/* ����load_texture
* ��ȡһ��BMP�ļ���Ϊ����
* ���ʧ�ܣ�����0������ɹ�������������
*/
GLuint load_texture(const char* file_name)
{
	GLint width, height, total_bytes;
	GLubyte* pixels = 0;
	GLuint last_texture_ID = 0, texture_ID = 0;

	// ���ļ������ʧ�ܣ�����
	FILE* pFile;
	fopen_s(&pFile, file_name, "rb");
	if (pFile == 0)
		return 0;

	// ��ȡ�ļ���ͼ��Ŀ�Ⱥ͸߶�
	fseek(pFile, 0x0012, SEEK_SET);
	fread(&width, 4, 1, pFile);
	fread(&height, 4, 1, pFile);
	fseek(pFile, BMP_Header_Length, SEEK_SET);

	// ����ÿ��������ռ�ֽ����������ݴ����ݼ����������ֽ���
	{
		GLint line_bytes = width * 3;
		while (line_bytes % 4 != 0)
			++line_bytes;
		total_bytes = line_bytes * height;
	}

	// �����������ֽ��������ڴ�
	pixels = (GLubyte*)malloc(total_bytes);
	if (pixels == 0)
	{
		fclose(pFile);
		return 0;
	}

	// ��ȡ��������
	if (fread(pixels, total_bytes, 1, pFile) <= 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// �Ծ;ɰ汾�ļ��ݣ����ͼ��Ŀ�Ⱥ͸߶Ȳ��ǵ������η�������Ҫ��������
	// ��ͼ���߳�����OpenGL�涨�����ֵ��Ҳ����
	{
		GLint max;
		glGetIntegerv(GL_MAX_TEXTURE_SIZE, &max);
		if (!power_of_two(width)
			|| !power_of_two(height)
			|| width > max
			|| height > max)
		{
			const GLint new_width = 256;
			const GLint new_height = 256; // �涨���ź��µĴ�СΪ�߳���������
			GLint new_line_bytes, new_total_bytes;
			GLubyte* new_pixels = 0;

			// ����ÿ����Ҫ���ֽ��������ֽ���
			new_line_bytes = new_width * 3;
			while (new_line_bytes % 4 != 0)
				++new_line_bytes;
			new_total_bytes = new_line_bytes * new_height;

			// �����ڴ�
			new_pixels = (GLubyte*)malloc(new_total_bytes);
			if (new_pixels == 0)
			{
				free(pixels);
				fclose(pFile);
				return 0;
			}

			// ������������
			gluScaleImage(GL_RGB,
				width, height, GL_UNSIGNED_BYTE, pixels,
				new_width, new_height, GL_UNSIGNED_BYTE, new_pixels);

			// �ͷ�ԭ�����������ݣ���pixelsָ���µ��������ݣ�����������width��height
			free(pixels);
			pixels = new_pixels;
			width = new_width;
			height = new_height;
		}
	}

	// ����һ���µ�������
	glGenTextures(1, &texture_ID);
	if (texture_ID == 0)
	{
		free(pixels);
		fclose(pFile);
		return 0;
	}

	// ���µ������������������������
	// �ڰ�ǰ���Ȼ��ԭ���󶨵������ţ��Ա��������лָ�
	GLint lastTextureID = last_texture_ID;
	glGetIntegerv(GL_TEXTURE_BINDING_2D, &lastTextureID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0,
		GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels);
	glBindTexture(GL_TEXTURE_2D, lastTextureID);  //�ָ�֮ǰ�������
	free(pixels);
	return texture_ID;
}


void polygon(int a, int b, int c, int d,int color)
{

	glBindTexture(GL_TEXTURE_2D, texture);//?
	glBegin(GL_POLYGON);
    //glColor3fv(colors[color]);
	glTexCoord2f(1.0f, 0.0f); glVertex3fv(vertices[a]);
	glTexCoord2f(0.0f, 0.0f); glVertex3fv(vertices[b]);
	glTexCoord2f(0.0f, 1.0f); glVertex3fv(vertices[c]);
	glTexCoord2f(1.0f, 1.0f); glVertex3fv(vertices[d]);
	glEnd();
}


void colorcube()
{
	polygon(0, 3, 2, 1, 1);
	polygon(2, 3, 7, 6, 2);
	polygon(0, 4, 7, 3, 3);
	polygon(1, 2, 6, 5, 4);
	polygon(4, 5, 6, 7, 5);
	polygon(0, 1, 5, 4, 6);
}


void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	colorcube();
	glutSwapBuffers();
}

void RotateCube()
{
	theta[axis] = 0.002;
	if (theta[axis] > 360.0) theta[axis] -= 360.0;
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	//�ƻ�ԭ��
	//glTranslatef(-x, -y, -z);
	//��ת
	glRotatef(theta[0], 1.0, 0.0, 0.0);
	glRotatef(theta[1], 0.0, 1.0, 0.0);
	glRotatef(theta[2], 0.0, 0.0, 1.0);
	//�ƻ�ԭλ
	//glTranslatef(x, y, z);
	glutPostRedisplay();
}

void RescaleCube()
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glScalef(scaleFactor[0], scaleFactor[1], scaleFactor[2]);
	//Reset
	scaleFactor[0] = scaleFactor[1] = scaleFactor[2] = 1;
	glutPostRedisplay();
}

void TranslateCube()
{
	//glMatrixMode(GL_MODELVIEW);
	//glLoadIdentity();
	glTranslatef(translateDelta[0], translateDelta[1], translateDelta[2]);
	x += translateDelta[0];
	y += translateDelta[1];
	z += translateDelta[2];
	translateDelta[0] = translateDelta[1] = translateDelta[2] = 0;
	glutPostRedisplay();
}

void keyboard(unsigned char c, int x, int y)
{
	switch (c)
	{
	case 'q':
		translateDelta[0] = 0.5;
		break;
	case 'w':
		translateDelta[1] = 0.5;
		break;
	case 'e':
		translateDelta[2] = 0.5;
		break;
	case 'a':
		translateDelta[0] = -0.5;
		break;
	case 's':
		translateDelta[1] = -0.5;
		break;
	case 'd':
		translateDelta[2] = -0.5;
		break;
	case 'i':
		scaleFactor[0] = 1.1;
		break;
	case 'o':
		scaleFactor[1] = 1.1;
		break;
	case 'p':
		scaleFactor[2] = 1.1;
		break;
	case 'j':
		scaleFactor[0] = 1/1.1;
		break;
	case 'k':
		scaleFactor[1] = 1/1.1;
		break;
	case 'l':
		scaleFactor[2] = 1/1.1;
		break;
	default:
		break;
	}
	TranslateCube();
	RescaleCube();
}

void mouse(int btn, int state, int x, int y)
{
	/*
	if (btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		axis = 0;
	if (btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN)
		axis = 1;
	if (btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
		axis = 2;
		*/
	if (state == GLUT_DOWN)
	{
		theta[axis] = 0;
		if (btn == GLUT_LEFT_BUTTON)
			axis = 0;
		if (btn == GLUT_MIDDLE_BUTTON)
			axis = 1;
		if (btn == GLUT_RIGHT_BUTTON)
			axis = 2;
		//RotateCube();
	}
}


void main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB |
		GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("colorcube");
	texture = load_texture(".//tex.bmp");
	glEnable(GL_TEXTURE_2D);
	//glutReshapeFunc(myReshape);
	glLoadIdentity();
	glutDisplayFunc(Display);
	glutIdleFunc(RotateCube);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
}
