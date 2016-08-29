#include "stdafx.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h> 
#include <iostream> 
#include <vector>
#include <GL/glut.h>

#include "Ekran.h"
#include "Transformacje.h"

using namespace std;
using namespace glm;

// zmienne globalne
GLFWwindow *mojeOkno = NULL;
GLuint vao = 0;
vector<GLfloat> liczba_wierzcholkow;
vector<GLfloat> poczatkowy_wierzcholek;
GLuint tekstury[5];

int main(void) {

	Ekran ekran;
	Transformacje trans;
	ekran.Inicjacja(mojeOkno);

	vao = ekran.WczytajObjekt("tekstury/Tiger.obj", liczba_wierzcholkow, poczatkowy_wierzcholek);
	GLuint shaders = ekran.WczytajShadery("vertex_shader.glsl", "fragment_shader.glsl");
	GLint transformacja = ekran.Znajdz_Zmienna(shaders, "macierz_przesuniecia");
	GLint viewm = ekran.Znajdz_Zmienna(shaders, "view_matrix");
	GLint perspm = ekran.Znajdz_Zmienna(shaders, "perspective_matrix");

	tekstury[0] = ekran.Wczytaj_Teksture("tekstury/tiger.bmp");
	glUniform1i(tekstury[0], 0);
//	tekstury[1] = ekran.Wczytaj_Teksture("tekstury/hulk/hair.bmp");
//	glUniform1i(tekstury[1], 0);

	float dx=0, dy=0 , promien = 0.8, angle = 0;
	mat4 wynik_trans(1.0);

	// kamera
	trans.ustawKamere();

	float move_speed = 1.0f;
	mat4 perspektywa(1.0);
	mat4 kamera(1.0);


	while (!glfwWindowShouldClose(mojeOkno))
	{
		if (glfwGetKey(mojeOkno, GLFW_KEY_LEFT) == GLFW_PRESS) { trans.KamerawLewo(move_speed); }
		if (glfwGetKey(mojeOkno, GLFW_KEY_RIGHT) == GLFW_PRESS) { trans.KamerawPrawo(move_speed); }
		if (glfwGetKey(mojeOkno, GLFW_KEY_DOWN) == GLFW_PRESS) { trans.KamerawTyl(move_speed); }
		if (glfwGetKey(mojeOkno, GLFW_KEY_UP) == GLFW_PRESS) {	trans.KamerawPrzod(move_speed);	}

		if (glfwGetKey(mojeOkno, GLFW_KEY_A) == GLFW_PRESS) { dx = dx - 0.05f; }
		if (glfwGetKey(mojeOkno, GLFW_KEY_D) == GLFW_PRESS) { dx = dx + 0.05f; }
		if (glfwGetKey(mojeOkno, GLFW_KEY_W) == GLFW_PRESS) { dy = dy + 0.05f; }
		if (glfwGetKey(mojeOkno, GLFW_KEY_S) == GLFW_PRESS) { dy = dy - 0.05f; }
		if (glfwGetKey(mojeOkno, GLFW_KEY_Q) == GLFW_PRESS) { dx = 0;  dy = 0; }
		if (glfwGetKey(mojeOkno, GLFW_KEY_E) == GLFW_PRESS) { trans.zerujKamere(); }

		angle += 1;
		trans.funkcja_Po_Okregu(promien, angle, dx, dy);
		wynik_trans = trans.przesun(dx, dy, 0.0);
		wynik_trans = trans.obroc(wynik_trans, angle / 15, false, true, false);
//		wynik_trans = trans.przesun(0.0, -2.5, 0.0);
		//		wynik_trans = mat4(1.0);

		trans.kamera(perspektywa, kamera);	// aktualizuje zmienne perspektywy i kamery
		glUniformMatrix4fv(perspm, 1, GL_FALSE, value_ptr(perspektywa));
		glUniformMatrix4fv(viewm, 1, GL_FALSE, value_ptr(kamera));
		glUniformMatrix4fv(transformacja, 1, GL_FALSE, value_ptr(wynik_trans));
		ekran.cls(0.0f, 0.0f, 0.3f);

		glUseProgram(shaders);
		glBindTexture(GL_TEXTURE_2D, tekstury[0]);
		for (int i = 0; i < poczatkowy_wierzcholek.size(); i++) {
			glBindVertexArray(vao);
			glBindTexture(GL_TEXTURE_2D, tekstury[i]);
			glDrawArrays(GL_TRIANGLES, poczatkowy_wierzcholek[i], liczba_wierzcholkow[i]);
		}

		ekran.LicznikFPS();
		ekran.swapBuffers();
	}


	// destruktor zamyka okno itp.
	return 0;
}

