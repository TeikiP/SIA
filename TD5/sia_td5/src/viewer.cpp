#include "viewer.h"
#include "camera.h"
#include "quad.h"

extern int WIDTH;
extern int HEIGHT;

using namespace Eigen;

Viewer::Viewer()
{
}

Viewer::~Viewer()
{
}

////////////////////////////////////////////////////////////////////////////////
// GL stuff

// initialize OpenGL context
void Viewer::init(int w, int h){
    _winWidth = w;
    _winHeight = h;

    // Couleur d'arrière plan
    glClearColor(0.0, 0.0, 0.0, 0.0);

    loadProgram();

    Quad* quad = new Quad();
    quad->init();
    quad->setTransformationMatrix( AngleAxisf((float)M_PI_2, Vector3f(-1,0,0)) * Scaling(20.f,20.f,1.f) * Translation3f(0,0,-0.5));
    _shapes.push_back(quad);
    _specularCoef.push_back(0.);

    Mesh* mesh = new Mesh();
    mesh->load(DATA_DIR"/models/tw.off");
    mesh->init();
    _shapes.push_back(mesh);
    _specularCoef.push_back(0.75);

    mesh = new Mesh();
    mesh->load(DATA_DIR"/models/sphere.off");
    mesh->init();
    mesh->setTransformationMatrix(Translation3f(0,0,2.f) * Scaling(0.5f) );
    _shapes.push_back(mesh);
    _specularCoef.push_back(0.2);


    _pointLight[0] = Sphere(0.025f);
    _pointLight[0].init();
    _pointLight[0].setTransformationMatrix(Affine3f(Translation3f(1,0.75,1)));
    _lightColor[0] = Vector3f(1,1,1);

    if (nb_lights >= 1) {
      _pointLight[1] = Sphere(0.025f);
      _pointLight[1].init();
      _pointLight[1].setTransformationMatrix(Affine3f(Translation3f(0,0.75,-1)));
      _lightColor[1] = Vector3f(1,0,0);
    }

    if (nb_lights >= 2) {
      _pointLight[2] = Sphere(0.025f);
      _pointLight[2].init();
      _pointLight[2].setTransformationMatrix(Affine3f(Translation3f(-1,0,1)));
      _lightColor[2] = Vector3f(0,0,1);
    }

    AlignedBox3f aabb;
    for(int i=0; i<_shapes.size(); ++i)
        aabb.extend(_shapes[i]->boundingBox());

    _cam.setSceneCenter(aabb.center());
    _cam.setSceneRadius(aabb.sizes().maxCoeff());
    _cam.setSceneDistance(_cam.sceneRadius() * 3.f);
    _cam.setMinNear(0.1f);
    _cam.setNearFarOffsets(-_cam.sceneRadius() * 100.f,
                            _cam.sceneRadius() * 100.f);
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));


    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);

    // FBO
    _fbo.init(_winWidth, _winHeight);
    _quad->init();

}

void Viewer::reshape(int w, int h){
    _winWidth = w;
    _winHeight = h;
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));
    glViewport(0, 0, w, h);
}


/*!
   callback to draw graphic primitives
 */
void Viewer::display()
{
    // update light position
    Vector3f lightPos[nb_lights];
    Vector4f lightPosH[nb_lights];

    for (int i=0; i<3; i++) {
			lightPos[i] = (_pointLight[i].getTransformationMatrix()*Vector4f(0,0,0,1)).head(3);

			if (i==0) { //Only one rotating light
	      lightPos[i][0] = cos(_lightAngle) + 0.5;
	      lightPos[i][2] = sin(_lightAngle) + 0.5;
	      _lightAngle += M_PI_2/100.0;
	      _pointLight[i].setTransformationMatrix(Affine3f(Translation3f(lightPos[i])));
			}

      lightPosH[i] << lightPos[i], 1.f;
    }


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    /* GBUFFER SHADER */
    _fbo.bind();

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _gbufferPrg.activate();

    glUniformMatrix4fv(_gbufferPrg.getUniformLocation("projection_matrix"),1,false,_cam.computeProjectionMatrix().data());
    glUniformMatrix4fv(_gbufferPrg.getUniformLocation("view_matrix"),1,false,_cam.computeViewMatrix().data());

    for(int i=0; i<_shapes.size(); ++i)
    {
        glUniformMatrix4fv(_gbufferPrg.getUniformLocation("model_matrix"),1,false,_shapes[i]->getTransformationMatrix().data());
        Matrix3f normal_matrix = (_cam.computeViewMatrix()*_shapes[i]->getTransformationMatrix()).linear().inverse().transpose();
        glUniformMatrix3fv(_gbufferPrg.getUniformLocation("normal_matrix"), 1, GL_FALSE, normal_matrix.data());
        glUniform1f(_gbufferPrg.getUniformLocation("specular_coef"),_specularCoef[i]);

        _shapes[i]->display(&_gbufferPrg);
    }

    _gbufferPrg.deactivate();

    /*_fbo.savePNG("fbo_colors", _fbo.renderedTexture);
    _fbo.savePNG("fbo_normals", _fbo.normalTexture);*/

    _fbo.unbind();


    /* DEFERRED SHADER */
    _deferredPrg.activate();

		glDisable(GL_DEPTH_TEST);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);

    glUniform4fv(_deferredPrg.getUniformLocation("light_pos0"),1,(_cam.computeViewMatrix()*lightPosH[0]).eval().data());
    glUniform4fv(_deferredPrg.getUniformLocation("light_pos1"),1,(_cam.computeViewMatrix()*lightPosH[1]).eval().data());
    glUniform4fv(_deferredPrg.getUniformLocation("light_pos2"),1,(_cam.computeViewMatrix()*lightPosH[2]).eval().data());
    glUniform3fv(_deferredPrg.getUniformLocation("light_col0"),1,_lightColor[0].data());
    glUniform3fv(_deferredPrg.getUniformLocation("light_col1"),1,_lightColor[1].data());
    glUniform3fv(_deferredPrg.getUniformLocation("light_col2"),1,_lightColor[2].data());

    glUniformMatrix4fv(_deferredPrg.getUniformLocation("inv_projection_matrix"),1,false,_cam.computeProjectionMatrix().inverse().eval().data());
    glUniform2fv(_deferredPrg.getUniformLocation("window_size"), 1, Vector2f(_winWidth, _winHeight).data());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _fbo.renderedTexture);
    glUniform1i(_deferredPrg.getUniformLocation("rendered_texture"), 0);

    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, _fbo.normalTexture);
    glUniform1i(_deferredPrg.getUniformLocation("normal_texture"), 1);

    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D, _fbo.depthTexture);
    glUniform1i(_deferredPrg.getUniformLocation("depth_texture"), 2);

    _quad->display(&_deferredPrg);

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);

    _deferredPrg.deactivate();


    /* BLINN SHADER */
    /*_blinnPrg.activate();

    glUniformMatrix4fv(_blinnPrg.getUniformLocation("projection_matrix"),1,false,_cam.computeProjectionMatrix().data());
    glUniformMatrix4fv(_blinnPrg.getUniformLocation("view_matrix"),1,false,_cam.computeViewMatrix().data());

    // update light position
    glUniform4fv(_blinnPrg.getUniformLocation("light_pos"),1,(_cam.computeViewMatrix()*lightPosH[0]).eval().data());

    // draw meshes
    for(int i=0; i<_shapes.size(); ++i)
    {
        glUniformMatrix4fv(_blinnPrg.getUniformLocation("model_matrix"),1,false,_shapes[i]->getTransformationMatrix().data());
        Matrix3f normal_matrix = (_cam.computeViewMatrix()*_shapes[i]->getTransformationMatrix()).linear().inverse().transpose();
        glUniformMatrix3fv(_blinnPrg.getUniformLocation("normal_matrix"), 1, GL_FALSE, normal_matrix.data());
        glUniform1f(_blinnPrg.getUniformLocation("specular_coef"),_specularCoef[i]);
        glUniform3fv(_blinnPrg.getUniformLocation("light_col"),1,_lightColor[0].data());

        _shapes[i]->display(&_blinnPrg);
    }

    _blinnPrg.deactivate();*/


    /* SIMPLE SHADER */
    // Draw pointlight sources
    _simplePrg.activate();

    glUniformMatrix4fv(_simplePrg.getUniformLocation("projection_matrix"),1,false,_cam.computeProjectionMatrix().data());
    glUniformMatrix4fv(_simplePrg.getUniformLocation("view_matrix"),1,false,_cam.computeViewMatrix().data());

    for (int i=0; i < nb_lights; i++) {
      glUniformMatrix4fv(_simplePrg.getUniformLocation("model_matrix"),1,false,_pointLight[i].getTransformationMatrix().data());
      glUniform3fv(_simplePrg.getUniformLocation("light_col"),1,_lightColor[i].data());
      _pointLight[i].display(&_simplePrg);
    }

    _simplePrg.deactivate();
}


void Viewer::updateScene()
{
    display();
}

void Viewer::loadProgram()
{
    _blinnPrg.loadFromFiles(DATA_DIR"/shaders/blinn.vert", DATA_DIR"/shaders/blinn.frag");
    _simplePrg.loadFromFiles(DATA_DIR"/shaders/simple.vert", DATA_DIR"/shaders/simple.frag");
    _gbufferPrg.loadFromFiles(DATA_DIR"/shaders/gbuffer.vert", DATA_DIR"/shaders/gbuffer.frag");
    _deferredPrg.loadFromFiles(DATA_DIR"/shaders/deferred.vert", DATA_DIR"/shaders/deferred.frag");
    checkError();
}

////////////////////////////////////////////////////////////////////////////////
// Events

/*!
   callback to manage mouse : called when user press or release mouse button
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::mousePressed(GLFWwindow *window, int button, int action)
{
    if(action == GLFW_PRESS) {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            _cam.startRotation(_lastMousePos);
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            _cam.startTranslation(_lastMousePos);
        }
        _button = button;
    }else if(action == GLFW_RELEASE) {
        if(_button == GLFW_MOUSE_BUTTON_LEFT)
        {
            _cam.endRotation();
        }
        else if(_button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            _cam.endTranslation();
        }
        _button = -1;
    }
}


/*!
   callback to manage mouse : called when user move mouse with button pressed
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::mouseMoved(int x, int y)
{
    if(_button == GLFW_MOUSE_BUTTON_LEFT)
    {
        _cam.dragRotate(Vector2f(x,y));
    }
    else if(_button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        _cam.dragTranslate(Vector2f(x,y));
    }
    _lastMousePos = Vector2f(x,y);
}

void Viewer::mouseScroll(double x, double y)
{
    _cam.zoom((y>0)? 1.1: 1./1.1);
}

/*!
   callback to manage keyboard interactions
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::keyPressed(int key, int action, int mods)
{
    if(key == GLFW_KEY_R && action == GLFW_PRESS)
        loadProgram();
}

void Viewer::charPressed(int key)
{
}
