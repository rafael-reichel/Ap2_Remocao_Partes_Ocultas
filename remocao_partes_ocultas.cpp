#include <GL/glut.h>
#include <stdio.h>
#include <string>

// Enumera��o das t�cnicas dispon�veis
enum Technique {
    BACKFACE_CULLING,
    PAINTERS_ALGORITHM,
    Z_BUFFER
};

// Vari�veis globais
Technique currentTechnique = BACKFACE_CULLING;
float angleY = 0.0f;
bool showHelp = true;

// Fun��o para desenhar texto na tela
void drawText(float x, float y, const char* text) {
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

// Fun��o para exibir informa��es de ajuda
void drawHelp() {
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 600, 0, 600);

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1.0f, 1.0f, 1.0f);
    drawText(20, 580, "TECNICAS DE RENDERIZACAO 3D - QUATRO CUBOS");

    const char* techniqueName = "";
    switch(currentTechnique) {
        case BACKFACE_CULLING: techniqueName = "BACK-FACE CULLING"; break;
        case PAINTERS_ALGORITHM: techniqueName = "PAINTER'S ALGORITHM"; break;
        case Z_BUFFER: techniqueName = "Z-BUFFER"; break;
    }

    drawText(20, 550, (std::string("Tecnica Atual: ") + techniqueName).c_str());
    drawText(20, 520, "Controles:");
    drawText(20, 490, "1 - Back-Face Culling");
    drawText(20, 460, "2 - Painter's Algorithm");
    drawText(20, 430, "3 - Z-Buffer");
    drawText(20, 400, "Setas - Rotacionar cena");
    drawText(20, 370, "H - Mostrar/ocultar ajuda");
    drawText(20, 340, "ESC - Sair");

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

// Fun��o de inicializa��o baseada na t�cnica selecionada
void init() {
    switch(currentTechnique) {
        case BACKFACE_CULLING:
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_CULL_FACE);
            glCullFace(GL_BACK);
            glFrontFace(GL_CCW);
            break;

        case PAINTERS_ALGORITHM:
            glDisable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
            break;

        case Z_BUFFER:
            glEnable(GL_DEPTH_TEST);
            glDisable(GL_CULL_FACE);
            break;
    }
}

// Fun��o para desenhar um quadrado colorido em profundidade Z (usado no Painter's Algorithm)
void drawQuad(float z, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, z);
    glVertex3f( 0.5, -0.5, z);
    glVertex3f( 0.5,  0.5, z);
    glVertex3f(-0.5,  0.5, z);
    glEnd();
}

// Fun��o para desenhar um cubo em posi��o espec�fica (usado no Z-Buffer e Back-Face Culling)
void drawCube(float x, float y, float z, float r, float g, float b, float size = 0.8) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(r, g, b);
    glutSolidCube(size);
    glPopMatrix();
}

// Fun��o principal de renderiza��o
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Configura��o da c�mera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, 1.0f, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0f, 1.5f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

    // Aplica rota��o
    glRotatef(angleY, 0, 1, 0);

    // Renderiza de acordo com a t�cnica selecionada
    switch(currentTechnique) {
        case BACKFACE_CULLING:
            // Quatro cubos em diferentes posi��es
            drawCube(-1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f); // Vermelho - esquerda, fundo
            drawCube(1.0f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f);  // Verde - direita, fundo
            drawCube(-1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f);  // Azul - esquerda, frente
            drawCube(1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f);   // Amarelo - direita, frente
            break;

        case PAINTERS_ALGORITHM:
            // Desenha quatro quadrados em ordem manual (do mais longe para o mais perto)
            drawQuad(-1.5f, 1.0f, 0.0f, 0.0f); // Vermelho (mais longe)
            drawQuad(-1.0f, 0.0f, 1.0f, 0.0f); // Verde
            drawQuad(-0.5f, 0.0f, 0.0f, 1.0f); // Azul
            drawQuad(0.0f, 1.0f, 1.0f, 0.0f);  // Amarelo (mais pr�ximo)
            break;

        case Z_BUFFER:
            // Desenha quatro cubos em diferentes profundidades e posi��es
            drawCube(-1.5f, 0.0f, -2.0f, 1.0f, 0.0f, 0.0f); // Vermelho - fundo esquerdo
            drawCube(1.5f, 0.0f, -1.5f, 0.0f, 1.0f, 0.0f); // Verde - fundo direito
            drawCube(-1.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f); // Azul - meio esquerdo
            drawCube(1.5f, 0.0f, -0.5f, 1.0f, 1.0f, 0.0f);  // Amarelo - meio direito
            break;
    }

    // Mostra ajuda se necess�rio
    if (showHelp) {
        drawHelp();
    }

    glutSwapBuffers();
}

// Fun��o de controle do teclado para rota��o
void specialKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) angleY -= 5.0f;
    else if (key == GLUT_KEY_RIGHT) angleY += 5.0f;
    glutPostRedisplay();
}

// Fun��o de controle do teclado para mudan�a de t�cnica
void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case '1':
            currentTechnique = BACKFACE_CULLING;
            init();
            break;
        case '2':
            currentTechnique = PAINTERS_ALGORITHM;
            init();
            break;
        case '3':
            currentTechnique = Z_BUFFER;
            init();
            break;
        case 'h':
        case 'H':
            showHelp = !showHelp;
            break;
        case 27: // ESC
            exit(0);
            break;
    }
    glutPostRedisplay();
}

// Fun��o principal
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Demonstracao de Tecnicas de Renderizacao 3D - Quatro Cubos");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);

    printf("Controles:\n");
    printf("1 - Back-Face Culling\n");
    printf("2 - Painter's Algorithm\n");
    printf("3 - Z-Buffer\n");
    printf("Setas - Rotacionar cena\n");
    printf("H - Mostrar/ocultar ajuda\n");
    printf("ESC - Sair\n");

    glutMainLoop();
    return 0;
}
