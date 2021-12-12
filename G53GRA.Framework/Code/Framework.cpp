#include "Framework.h"


Framework::Framework(const std::string& filename) : Framework()
{
	texID = Scene::GetTexture(filename);
}

void Framework::Display()
{
	glPushMatrix();
	// Save current style attributes
	glPushAttrib(GL_ALL_ATTRIB_BITS);
	// Set colour to pale grey
	glColor3ub(250, 250, 250);

	glTranslatef(pos[0], pos[1], pos[2]);
	glScalef(scale[0], scale[1], scale[2]);

	DrawFramework();

	// Revert style attributes
	glPopAttrib();
	glPopMatrix();
}

void Framework::drawCylinder(GLdouble r, GLdouble h)
{
	GLUquadricObj* cylinder;
	glPushMatrix();
	glRotatef(-90, 1, 0, 0);
	cylinder = gluNewQuadric();
	gluCylinder(cylinder, r, r, h, 10, 1);
	glPopMatrix();

}

void Framework::DrawFramework()
{
	glPushMatrix();
		glTranslatef(0, -10, 0);
		glRotatef(90, 0, 1, 0);
		glColor3ub(240, 190, 0);
		glPushMatrix();

			for (size_t i = 0; i < 6; i++)
			{
				if (i < 4) {
					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(-90, 0, 0, 1);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 405.f);
					glPopMatrix();

					for (size_t j = 0; j < 5; j++)
					{
						drawCylinder(2.5f, 120.f);
						glTranslatef(100, 0, 0);
					}
					glTranslatef(-500, 0, 100);
				}
				else if (i == 4)
				{
					glTranslatef(100, 0, 0);
					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(-90, 0, 0, 1);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 305.f);
					glPopMatrix();
					for (size_t j = 0; j < 4; j++)
					{
						drawCylinder(2.5f, 120.f);
						glTranslatef(100, 0, 0);
					}
					glTranslatef(-300, 0, 100);
				}
				else
				{
					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(-90, 0, 0, 1);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 205.f);
					glPopMatrix();
					for (size_t k = 0; k < 3; k++)
					{
						drawCylinder(2.5f, 120.f);
						glTranslatef(100, 0, 0);
					}
				}
			}
		glPopMatrix();

		//glTranslatef(0, 118.75, 0);

		glPushMatrix();

			for (size_t i = 0; i < 5; i++)
			{
				if (i == 0) {
					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(90, 1, 0, 0);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 305.f);
					glPopMatrix();

					glTranslatef(100, 0, 0);
				}
				else if (i == 1)
				{

					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(90, 1, 0, 0);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 405.f);
					glPopMatrix();

					glTranslatef(100, 0, 0);
				}
				else
				{
					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(90, 1, 0, 0);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 505.f);
					glPopMatrix();

					glTranslatef(100, 0, 0);
				}
			}
		glPopMatrix();


		// level 2 ===============================
		glTranslatef(100, 120, 0);
		glColor3ub(60, 120, 130);
		glPushMatrix();

			for (size_t i = 0; i < 5; i++)
			{
				if (i < 4) {
					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(-90, 0, 0, 1);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 305.f);
					glPopMatrix();

					for (size_t j = 0; j < 4; j++)
					{
						drawCylinder(2.5f, 120.f);
						glTranslatef(100, 0, 0);
					}
					glTranslatef(-400, 0, 100);
				}
				else if (i == 4)
				{
					glTranslatef(200, 0, 0);
					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(-90, 0, 0, 1);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 105.f);
					glPopMatrix();
					for (size_t j = 0; j < 2; j++)
					{
						drawCylinder(2.5f, 120.f);
						glTranslatef(100, 0, 0);
					}

				}

			}
		glPopMatrix();

		//glTranslatef(0, 118.75, 0);

		glPushMatrix();

			for (size_t i = 0; i < 4; i++)
			{
				if (i < 2)
				{

					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(90, 1, 0, 0);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 305.f);
					glPopMatrix();

					glTranslatef(100, 0, 0);
				}
				else
				{
					glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(90, 1, 0, 0);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 405.f);
					glPopMatrix();

					glTranslatef(100, 0, 0);
				}
			}
		glPopMatrix();


		// level 3 ===============================
		glTranslatef(100, 120, 0);
		glColor3ub(150, 30, 30);
		glPushMatrix();

			for (size_t i = 0; i < 4; i++)
			{
				glPushMatrix();
				glTranslatef(0, 118.75, 0);
				glRotatef(-90, 0, 0, 1);
				glTranslatef(0, -2.5, 0);
				drawCylinder(2.5f, 205.f);
				glPopMatrix();

				for (size_t j = 0; j < 3; j++)
				{
					drawCylinder(2.5f, 120.f);
					glTranslatef(100, 0, 0);
				}
				glTranslatef(-300, 0, 100);

			}
		glPopMatrix();

		//glTranslatef(0, 118.75, 0);

		glPushMatrix();

			for (size_t i = 0; i < 3; i++)
			{
				glPushMatrix();
					glTranslatef(0, 118.75, 0);
					glRotatef(90, 1, 0, 0);
					glTranslatef(0, -2.5, 0);
					drawCylinder(2.5f, 305.f);
				glPopMatrix();

				glTranslatef(100, 0, 0);
			}
		glPopMatrix();

	glPopMatrix();
}