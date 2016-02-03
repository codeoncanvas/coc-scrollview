#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "ciScrollView.h"
#include "Grid.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class ScrollViewSampleApp : public App {
  public:
	void setup() override;
	void mouseDown( MouseEvent event ) override;
	void update() override;
	void draw() override;
	void cleanup() override;

	coc::Rect screenRect;
	coc::Rect windowRect;
	coc::Rect contentRect;
	coc::ciScrollView scrollView;

	Grid grid;

	vec2 touchPoint;
	float touchTime = 0.0;

	gl::GlslProgRef		glsl;
};

void ScrollViewSampleApp::setup()
{

	glsl = gl::getStockShader( gl::ShaderDef().color() );
	glsl->bind();

	grid.setup(2048, 2048);

	screenRect.setW( getWindowWidth() );
	screenRect.setH( getWindowHeight() );

	windowRect.setW( (int)(screenRect.getWidth() * 0.9) );
	windowRect.setH( (int)(screenRect.getHeight() * 0.9) );
	windowRect.setX( (int)((screenRect.getWidth() - windowRect.getWidth()) * 0.5) );
	windowRect.setY( (int)((screenRect.getHeight() - windowRect.getHeight()) * 0.5) );

	contentRect.setW( grid.getWidth() );
	contentRect.setH( grid.getHeight() );

	//----------------------------------------------------------
	scrollView.setWindowRect(windowRect); // window size and position of scroll view.
	scrollView.setContentRect(contentRect); // the pixel size of the content being displayed in scroll view.
	scrollView.fitContentToWindow(coc::COC_ASPECT_RATIO_KEEP); // fits content into window, works with ofAspectRatioMode values.

	scrollView.setScrollEasing(0.3); // smoothness of scrolling, between 0 and 1.
	scrollView.setBounceBack(0.3); // the speed of bounce back, between 0 and 1.
	scrollView.setDragVelocityDecay(0.9); // the speed of decay of drag velocity after release, between 0 and 1.
	scrollView.setUserInteraction(true); // enable / disable mouse or touch interaction.

	scrollView.setDoubleTapZoom(true); // enable double tap zoom.
	scrollView.setDoubleTapZoomIncrement(1.0); // the increment value of zoom on double tap, between 0 and 1.
	scrollView.setDoubleTapZoomIncrementTimeInSec(0.3); // the time amount of time for zoom increment.
	scrollView.setDoubleTapRegistrationTimeInSec(0.25); // the time threshold between taps for double tap event to register.
	scrollView.setDoubleTapRegistrationDistanceInPixels(20); // the distance threshold between taps for double tap event to register.

	scrollView.setup(); // setup must always be called at the end of scroll view config.

}

void ScrollViewSampleApp::mouseDown( MouseEvent event )
{
}

void ScrollViewSampleApp::update()
{
	scrollView.update();
}

void ScrollViewSampleApp::draw()
{
	gl::clear( Color( 0, 0, 0 ) );

	// ofxScrollView returns a matrix to do any transformations manually,
	// otherwise drawing things between begin() and end() methods will also do the trick.

	scrollView.begin();
	grid.draw();
	scrollView.end();

	gl::color( Color( 0, 0, 0 ) );

	gl::VertBatch vb(GL_LINES);
	vb.vertex(screenRect.x1, screenRect.y1);
	vb.vertex(screenRect.x2, screenRect.y1);
	vb.vertex(screenRect.x2, screenRect.y2);
	vb.vertex(screenRect.getX(), screenRect.y2);
//	ofNextContour();
	vb.vertex(windowRect.x1, windowRect.y1);
	vb.vertex(windowRect.x2, windowRect.y1);
	vb.vertex(windowRect.x2, windowRect.y2);
	vb.vertex(windowRect.x1, windowRect.y2);

	vb.draw();

	gl::clear( Color( 1,1,1 ) );
	gl::drawStrokedRect(windowRect);
}

void ScrollViewSampleApp::cleanup()
{
	scrollView.setUserInteraction(false); // always remember to disable user interaction when killing the scrollview class.
}

CINDER_APP( ScrollViewSampleApp, RendererGl )
