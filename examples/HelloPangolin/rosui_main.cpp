

#include <pangolin/pangolin.h>
#include <pangolin/scene/axis.h>
#include <pangolin/scene/scenehandler.h>

#include <glm/glm.hpp>
#include <glm/vec3.hpp>
#include <iostream>

//     y
//      |_ x
//     /                                                     
//   z



class CamOnUI{

public:	
	glm::vec3 pos;
	GLfloat f_length;
	glm::vec3 imgMidPos;
	glm::vec3 imgCornPos[4]; 
	enum{ LT=0, LB=1, RT=2, RB=3 }; // Left Top Left Bottom......
	
	GLfloat Rx;
	GLfloat Ry; 
	GLfloat Rz;
 
	const GLfloat imgPlan_w = 0.8;
	const GLfloat imgPlan_h = 0.6; 

	CamOnUI();
	CamOnUI( glm::vec3 const &in_pos, GLfloat const &f, GLfloat const &rotateAngleX, GLfloat const &rotateAngleY, GLfloat const &rotateAngleZ){
		pos = in_pos;
		f_length = f;	
		imgMidPos = pos + glm::vec3(f,0,0); 		
		
		Rx = rotateAngleX;
		Ry = rotateAngleY;
		Rz = rotateAngleZ;
	
		imgCornPos[ LT ] = glm::vec3(imgMidPos.x,imgMidPos.y+imgPlan_h*0.5,imgMidPos.z-imgPlan_w*0.5);  
		imgCornPos[ LB ] = glm::vec3(imgMidPos.x,imgMidPos.y-imgPlan_h*0.5,imgMidPos.z-imgPlan_w*0.5);  
		imgCornPos[ RT ] = glm::vec3(imgMidPos.x,imgMidPos.y+imgPlan_h*0.5,imgMidPos.z+imgPlan_w*0.5);  
		imgCornPos[ RB ] = glm::vec3(imgMidPos.x,imgMidPos.y-imgPlan_h*0.5,imgMidPos.z+imgPlan_w*0.5);  

	
	};


	void drawCam() const{
		
		  	glPushMatrix();  //先存入所有座標 避免大家都受此座標系旋轉影響 
  			glTranslatef(pos.x, pos.y, pos.z); //轉換座標系
  			glRotatef( Ry, 0, 1.0, 0);
  			glRotatef( Rz, 0, 0, 1.0);
  			glRotatef( Rx, 1.0, 0, 0);
			glTranslatef(-1*pos.x, -1*pos.y, -1*pos.z); //轉回原座標系

			
			glBegin( GL_LINES ); //只畫受旋轉影響的Cam
				glColor3f(1.0,0,0);
				glVertex3f( imgCornPos[LT].x ,imgCornPos[LT].y, imgCornPos[LT].z);
				glVertex3f( imgCornPos[RT].x ,imgCornPos[RT].y, imgCornPos[RT].z);
				glVertex3f( imgCornPos[RT].x ,imgCornPos[RT].y, imgCornPos[RT].z);
 		    	glVertex3f( imgCornPos[RB].x ,imgCornPos[RB].y, imgCornPos[RB].z);
				glVertex3f( imgCornPos[RB].x ,imgCornPos[RB].y, imgCornPos[RB].z);
				glVertex3f( imgCornPos[LB].x ,imgCornPos[LB].y, imgCornPos[LB].z);
				glVertex3f( imgCornPos[LB].x ,imgCornPos[LB].y, imgCornPos[LB].z); 
				glVertex3f( imgCornPos[LT].x ,imgCornPos[LT].y, imgCornPos[LT].z);
				
				glColor3f(1.0,0.1,0);	
				glVertex3f( imgCornPos[RT].x ,imgCornPos[RT].y, imgCornPos[RT].z);
				glVertex3f( pos.x ,pos.y ,pos.z);
				glVertex3f( imgCornPos[RB].x ,imgCornPos[RB].y, imgCornPos[RB].z);
				glVertex3f( pos.x ,pos.y ,pos.z);  
				glVertex3f( imgCornPos[LB].x ,imgCornPos[LB].y, imgCornPos[LB].z); 
		 		glVertex3f( pos.x ,pos.y ,pos.z);  	
				glVertex3f( imgCornPos[LT].x ,imgCornPos[LT].y, imgCornPos[LT].z);
				glVertex3f( pos.x ,pos.y ,pos.z);  
			glEnd();

    		glPopMatrix();  


	}

};


int X,Y,Z=0;
void fX(){X++;}
void fY(){Y++;}
void fZ(){Z++;}


void UISwitch(){

	std::cout << "You typed ctrl-r or pushed reset" << std::endl;
}


int main( int /*argc*/, char** /*argv*/ )
{
    pangolin::CreateWindowAndBind("Main",1024,768);
    glEnable(GL_DEPTH_TEST);

    // Define Projection and initial ModelView matrix
    pangolin::OpenGlRenderState s_cam(
        pangolin::ProjectionMatrix(768,768,420,420,384,384,0.2,100),
        pangolin::ModelViewLookAt(-10,3,-10, 0,0,0, pangolin::AxisY)
    );

	
	const int UI_WIDTH = 256; //(pixels) 

 	// Create Interactive View in window
 	pangolin::View& d_cam = pangolin::CreateDisplay();
 	d_cam.SetBounds(0.0, 1.0, 0.0, 1.0, -1024.0f/768.0f);
 	pangolin::Handler3D handler(s_cam); 
	d_cam.SetHandler(&handler);                                         

	 // Add named Panel and bind to variables beginning 'ui'
	 // A Panel is just a View with a default layout and input handling    
	pangolin::CreatePanel("ui")
    	 .SetBounds(0.0,1.0, 0.0, pangolin::Attach::Pix(UI_WIDTH));

	pangolin::Var<std::function<void(void)> > ui_switch("ui.SwitchTab", UISwitch);

	pangolin::Var<bool> ui_cam1("ui.Cam1",false,true);
	pangolin::Var<GLfloat > ui_cam1_posx("ui.Cam1_posx",0,0,0);
	pangolin::Var<GLfloat > ui_cam1_posy("ui.Cam1_posy",0,0,0);
    pangolin::Var<GLfloat > ui_cam1_posz("ui.Cam1_posz",0,0,0);
	pangolin::Var<GLfloat > ui_cam1_rotx("ui.Cam1_Rx",0,0,0);
	pangolin::Var<GLfloat > ui_cam1_roty("ui.Cam1_Ry",0,0,0);
	pangolin::Var<GLfloat > ui_cam1_rotz("ui.Cam1_Rz",0,0,0);
	
	pangolin::Var<bool> ui_cam2("ui.Cam2",false,true);  
    pangolin::Var<GLfloat > ui_cam2_posx("ui.Cam2_posx",0,0,0);
    pangolin::Var<GLfloat > ui_cam2_posy("ui.Cam2_posy",0,0,0);
    pangolin::Var<GLfloat > ui_cam2_posz("ui.Cam2_posz",0,0,0);
	pangolin::Var<GLfloat > ui_cam2_rotx("ui.Cam2_Rx",0,0,0);
	pangolin::Var<GLfloat > ui_cam2_roty("ui.Cam2_Ry",0,0,0);
	pangolin::Var<GLfloat > ui_cam2_rotz("ui.Cam2_Rz",0,0,0);

	pangolin::Var<bool> ui_cam3("ui.Cam3",false,true);  
	pangolin::Var<GLfloat > ui_cam3_posx("ui.Cam3_posx",0,0,0);
	pangolin::Var<GLfloat > ui_cam3_posy("ui.Cam3_posy",0,0,0);
	pangolin::Var<GLfloat > ui_cam3_posz("ui.Cam3_posz",0,0,0);
	pangolin::Var<GLfloat > ui_cam3_rotx("ui.Cam3_Rx",0,0,0);
	pangolin::Var<GLfloat > ui_cam3_roty("ui.Cam3_Ry",0,0,0);
	pangolin::Var<GLfloat > ui_cam3_rotz("ui.Cam3_Rz",0,0,0);

	// Add named OpenGL viewport to window and provide 3D Handler
	// SetBound 設定邊界 View & pangolin::View::
			//SetBounds(Attach bottom,Attach top,Attach left,Attach right,double aspect ) 
			// Attach = [0,1] aspect = width / height pixels



	pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL + 'x', fX);
	pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL + 'y', fY);
	pangolin::RegisterKeyPressCallback(pangolin::PANGO_CTRL + 'z', fZ);



	CamOnUI cam1( glm::vec3(-0.9,3.2,3.5) , 0.5, 0 ,87, -20);
	CamOnUI cam2( glm::vec3(3.2,3.1,-2.0) , 0.5, 0, 0, 200);
	CamOnUI cam3( glm::vec3(-1.2,3.0,-4.0) , 0.5, 0, -80,-60);    		

	while( !pangolin::ShouldQuit() )
    {
        // Clear screen and activate view to render into
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		d_cam.Activate(s_cam);
		glBegin( GL_LINES );
			glColor3f(1.0,1.0,1.0);
			for(int i=-10;i<=10;i++){
				glVertex3i(i,0,-10);
				glVertex3i(i,0,10);
				glVertex3i(-10,0,i);
				glVertex3i(10,0,i);
			}
		glEnd();


		cam1.drawCam();
		cam2.drawCam();
		cam3.drawCam();

		ui_cam1_posx = cam1.pos.x;
		ui_cam1_posy = cam1.pos.y;
		ui_cam1_posz = cam1.pos.z;
		ui_cam1_rotx = cam1.Rx;
		ui_cam1_roty = cam1.Ry;
		ui_cam1_rotz = cam1.Rz;

		ui_cam2_posx = cam2.pos.x;
		ui_cam2_posy = cam2.pos.y;
		ui_cam2_posz = cam2.pos.z;
 		ui_cam2_rotx = cam2.Rx;
 		ui_cam2_roty = cam2.Ry;
 		ui_cam2_rotz = cam2.Rz; 

		ui_cam3_posx = cam3.pos.x;
		ui_cam3_posy = cam3.pos.y;
		ui_cam3_posz = cam3.pos.z;
		ui_cam3_rotx = cam3.Rx;
		ui_cam3_roty = cam3.Ry;     
		ui_cam3_rotz = cam3.Rz; 




		// Swap frames and Process Events
        pangolin::FinishFrame();
    }

    return 0;
}
                                                                                   

