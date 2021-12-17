#include "Wall.h"


Wall::Wall(const std::string& filename, int walltype) : Wall()
{
	texID = Scene::GetTexture(filename);
	type = walltype;
}

void Wall::Display()
{

	glPushMatrix();
	if (type == 0)
	{
		DrawWall();
		glRotatef(90.f, 0.f, 1.f, 0.f);
		DrawWall();
		glRotatef(90.f, 0.f, 1.f, 0.f);
		DrawWall();
		glRotatef(90.f, 0.f, 1.f, 0.f);
		DrawWall();
	}
	else
	{
		DrawCloudWall();
		glRotatef(90.f, 0.f, 1.f, 0.f);
		DrawCloudWall();
		glRotatef(90.f, 0.f, 1.f, 0.f);
		DrawCloudWall();
		glRotatef(90.f, 0.f, 1.f, 0.f);
		DrawCloudWall();
	}
	glPopMatrix();

	
	//Draw fense
	glPushMatrix();
		glTranslatef(-1100, -100, -1098);

		glPushMatrix();
			glTranslatef(1100, 60, 0);
			glScalef(2200, 10, 2);
			glColor3ub(40, 100, 110);
			DrawCube();
		glPopMatrix();

		glPushMatrix();
			glTranslatef(1100, 15, 0);
			glScalef(2200, 10, 2);
			glColor3ub(40, 100, 110);
			DrawCube();
		glPopMatrix();

		for (size_t i = 0; i < 15; i++)
		{
			DrawFenceGroup();
		}
		glTranslatef(35, 0, 0);
		DrawFence(240, 190, 0);
		glTranslatef(35, 0, 0);
		DrawFence(60, 120, 130);
	glPopMatrix();

	glPushMatrix();
		glRotatef(90, 0, 1, 0);
		glTranslatef(-1100, -100, -1098);
	
		glPushMatrix();
		glTranslatef(1100, 60, 0);
		glScalef(2200, 10, 2);
		glColor3ub(40, 100, 110);
		DrawCube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1100, 15, 0);
		glScalef(2200, 10, 2);
		glColor3ub(40, 100, 110);
		DrawCube();
		glPopMatrix();
	
		for (size_t i = 0; i < 15; i++)
		{
			DrawFenceGroup();
		}
		glTranslatef(35, 0, 0);
		DrawFence(240, 190, 0);
		glTranslatef(35, 0, 0);
		DrawFence(60, 120, 130);
	glPopMatrix();

	glPushMatrix();
		glRotatef(180, 0, 1, 0);
		glTranslatef(-1100, -100, -1098);

		glPushMatrix();
		glTranslatef(1100, 60, 0);
		glScalef(2200, 10, 2);
		glColor3ub(40, 100, 110);
		DrawCube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1100, 15, 0);
		glScalef(2200, 10, 2);
		glColor3ub(40, 100, 110);
		DrawCube();
		glPopMatrix();

		for (size_t i = 0; i < 15; i++)
		{
			DrawFenceGroup();
		}
		glTranslatef(35, 0, 0);
		DrawFence(240, 190, 0);
		glTranslatef(35, 0, 0);
		DrawFence(60, 120, 130);
	glPopMatrix();

	glPushMatrix();
		glRotatef(270, 0, 1, 0);
		glTranslatef(-1100, -100, -1098);

		glPushMatrix();
		glTranslatef(1100, 60, 0);
		glScalef(2200, 10, 2);
		glColor3ub(40, 100, 110);
		DrawCube();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(1100, 15, 0);
		glScalef(2200, 10, 2);
		glColor3ub(40, 100, 110);
		DrawCube();
		glPopMatrix();

		for (size_t i = 0; i < 15; i++)
		{
			DrawFenceGroup();
		}
		glTranslatef(35, 0, 0);
		DrawFence(240, 190, 0);
		glTranslatef(35, 0, 0);
		DrawFence(60, 120, 130);
	glPopMatrix();
	
}

void Wall::DrawWall()
{
	// Draws an exciting chequered floor
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_COLOR_MATERIAL);
	float bDiffuse[] = { 0.0f,0.0f,0.0f,1.0f }; //black
	float wDiffuse[] = { 1.0f,1.0f,1.0f,1.0f }; //white
	float specular[] = { 0.86f,0.75f,0.61f,1.0f };
	float shininess = 1.0f;

	// Tell openGL which texture buffer to use
	glBindTexture(GL_TEXTURE_2D, texID);


	glBegin(GL_QUADS);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));
	glColor3ub(172, 146, 112); //219, 191, 156(172, 146, 112)
	for (int i = -11; i < 11; i++)
	{
		for (int j = -1; j < 6; j++)
		{
			/*if (i % 2)
			{
				if (j % 2)
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(bDiffuse));
				else
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(wDiffuse));
			}
			else
			{
				if (j % 2)
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(wDiffuse));
				else
					glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, static_cast<GLfloat*>(bDiffuse));
			}*/

			glNormal3f(0.0f, 0.0f, 1.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], scale[2] * static_cast<float>(j) + scale[2], 1100.0f);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], scale[2] * static_cast<float>(j), 1100.0f);
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i), scale[2] * static_cast<float>(j), 1100.0f);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i), scale[2] * static_cast<float>(j) + scale[2], 1100.0f);
		}
	}
	glEnd();

	//glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);

	glPopAttrib();
	glPopMatrix();
}

void Wall::DrawCloudWall()
{
	// Draws an exciting chequered floor
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_COLOR_MATERIAL);
	float bDiffuse[] = { 0.0f,0.0f,0.0f,1.0f }; //black
	float wDiffuse[] = { 1.0f,1.0f,1.0f,1.0f }; //white
	float specular[] = { 0.86f,0.75f,0.61f,1.0f };
	//float specular[] = { 0.f,0.f,0.f,1.0f };
	float shininess = 128.0f;

	// Tell openGL which texture buffer to use
	glBindTexture(GL_TEXTURE_2D, texID);


	glBegin(GL_QUADS);
	glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));
	glColor3ub(255, 255, 255); //219, 191, 156


	glNormal3f(0.0f, 0.0f, 1.0f);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(scale[0] * 10 + scale[0], scale[2] * 5 + scale[2], 1100.0f);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(scale[0] * 10 + scale[0], scale[2] * -1, 1100.0f);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(scale[0] * -11, scale[2] * -1, 1100.0f);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(scale[0] * -11, scale[2] * 5 + scale[2], 1100.0f);

	glEnd();

	//glEnable(GL_COLOR_MATERIAL);
	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);

	glPopAttrib();
	glPopMatrix();
}

void Wall::DrawCube()
{
	// This function draws a unit cube centered around the origin

	glBegin(GL_QUADS);
	// Front
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	// Back
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	// Left
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	// Right
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	// Top
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, 0.5f);
	glVertex3f(0.5f, 0.5f, -0.5f);
	glVertex3f(-0.5f, 0.5f, -0.5f);
	// Bottom
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(-0.5f, -0.5f, 0.5f);
	glVertex3f(-0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, -0.5f);
	glVertex3f(0.5f, -0.5f, 0.5f);
	glEnd();
}

void Wall::DrawFence(int r, int g, int b) {
	glColor3ub(r, g, b);
	glPushMatrix();

	glPushMatrix();
	glRotatef(180, 0, 1, 0);
	glTranslatef(-5, 80, 0);
	glRotatef(-30, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.f, 0.f, -2.f);
	glVertex3f(-0.f, 0.f, 2.f);
	glVertex3f(-0.f, 10.f, 2.f);
	glVertex3f(-0.f, 10.f, -2.f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 80, 0);
	glRotatef(-30, 0, 0, 1);
	glBegin(GL_QUADS);
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(-0.f, 0.f, -2.f);
	glVertex3f(-0.f, 0.f, 2.f);
	glVertex3f(-0.f, 10.f, 2.f);
	glVertex3f(-0.f, 10.f, -2.f);
	glEnd();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 80, 2);
	glBegin(GL_TRIANGLES);

	glNormal3f(0.0f, 1.0f, 0.1f);
	glVertex3f(-5.0f, 0.0f, 0.0);
	glVertex3f(5.0f, 0.0f, 0.0f);
	glVertex3f(0.0f, 5.0f * float(sqrt(3)), 0.0f);
	// stop drawing triangles
	glEnd();
	glPopMatrix();

	glTranslatef(0, 40, 0);
	glScalef(10.0f, 80.0f, 4.0f);
	DrawCube();

	glPopMatrix();
}

void Wall::DrawFenceGroup()
{
	glTranslatef(35, 0, 0);
	DrawFence(240, 190, 0);
	glTranslatef(35, 0, 0);
	DrawFence(60, 120, 130);
	glTranslatef(35, 0, 0);
	DrawFence(150, 30, 30);
	glTranslatef(35, 0, 0);
	DrawFence(60, 120, 130);
}