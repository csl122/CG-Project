#include "Floor.h"

// The sandy floor
Floor::Floor(const std::string& filename, int floortype) : Floor()
{
	texID = Scene::GetTexture(filename);
	type = floortype;
}

void Floor::Display()
{
	// Always push before making any changes
	glPushMatrix();

	glBegin(GL_QUADS);

	glColor3ub(205, 205, 205);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-1100, -99.0f, -705);
	glVertex3f(-1100, -99.0f,-695);
	glVertex3f(1100, -99.0f, -695);
	glVertex3f(1100, -99.0f, -705);


	glEnd();

	if (type == 0)
	{
		DrawSand();
	}
	else
	{
		DrawPath();
	}
	glPopMatrix();

}

//sandy playground
void Floor::DrawSand()
{
	// Draws an exciting chequered floor
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	float specular[] = { 0.86f,0.75f,0.61f,1.0f };
	float shininess = 1.0f;

	// Tell openGL which texture buffer to use
	glBindTexture(GL_TEXTURE_2D, texID);


	glBegin(GL_QUADS);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));
	glColor3ub(172, 146, 112); //219, 191, 156
	for (int i = -11; i < 11; i++)
	{
		for (int j = -11; j < 11; j++)
		{

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], -100.0f, scale[2] * static_cast<float>(j) + scale[2]);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], -100.0f, scale[2] * static_cast<float>(j));
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i), -100.0f, scale[2] * static_cast<float>(j));
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i), -100.0f, scale[2] * static_cast<float>(j) + scale[2]);
		}
	}
	glEnd();

	glDisable(GL_COLOR_MATERIAL);
	glBindTexture(GL_TEXTURE_2D, NULL);
	// Stop performing texturing
	glDisable(GL_TEXTURE_2D);

	glPopAttrib();
	glPopMatrix();
}

// path in the tunnel
void Floor::DrawPath()
{
	// Draws an exciting chequered floor
	glPushMatrix();
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	// Enable Texturing
	glEnable(GL_TEXTURE_2D);
	//glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_COLOR_MATERIAL);
	float specular[] = { 0.86f,0.75f,0.61f,1.0f };
	float shininess = 1.0f;

	// Tell openGL which texture buffer to use
	glBindTexture(GL_TEXTURE_2D, texID);


	glBegin(GL_QUADS);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, static_cast<GLfloat*>(specular));
	glMaterialf(GL_FRONT, GL_SHININESS, static_cast<GLfloat>(shininess));
	glColor3ub(172, 146, 112); //219, 191, 156
	for (int i = -3; i < 3; i++)
	{
		for (int j = -6; j < 6; j++)
		{

			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 1200.0f, scale[2] * static_cast<float>(j) + scale[2]);
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i) + scale[0], 1200.0f, scale[2] * static_cast<float>(j));
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(scale[0] * static_cast<float>(i), 1200.0f, scale[2] * static_cast<float>(j));
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(scale[0] * static_cast<float>(i), 1200.0f, scale[2] * static_cast<float>(j) + scale[2]);
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