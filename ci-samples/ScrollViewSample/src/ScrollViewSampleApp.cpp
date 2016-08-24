#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"

#include "ciScrollView.h"
#include "Grid.h"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace coc;

class ScrollViewSampleApp : public App {
  public:
	void setup() override;
	void update() override;
	void draw() override;
    void cleanup() override;
    void mouseMove( MouseEvent event ) override;
    void mouseDown( MouseEvent event ) override;
    void mouseDrag( MouseEvent event ) override;
    void mouseUp( MouseEvent event ) override;

	Rectf windowRect;
	Rectf contentRect;
	ciScrollViewRef scrollView;

	Grid grid;
    
    bool bUserInteractionManual;
};

static void prepareSettings( App::Settings *settings ) {
    settings->setWindowSize(1024, 768);
}

void ScrollViewSampleApp::setup() {

	grid.setup(2048, 2048);
    
    windowRect = Rectf(getWindowBounds()) * .9;
    windowRect.offsetCenterTo(getWindowBounds().getCenter());

    contentRect = Rectf(0,0,grid.getWidth(),grid.getHeight());
    
    bUserInteractionManual = true;

	//----------------------------------------------------------
    scrollView = ciScrollView::create();
    scrollView->setWindowRect( windowRect ); // window size and position of scroll view.
	scrollView->setContentRect( contentRect ); // the pixel size of the content being displayed in scroll view.
//	scrollView->fitContentToWindow(coc::COC_ASPECT_RATIO_KEEP); // fits content into window, works with ofAspectRatioMode values.

	scrollView->setScrollEasing(0.3); // smoothness of scrolling, between 0 and 1.
	scrollView->setBounceEasing(0.5); // the speed of bounce back, between 0 and 1.
	scrollView->setDragVelocityDecay(0.9); // the speed of decay of drag velocity after release, between 0 and 1.
//	scrollView->setUserInteraction((bUserInteractionManual == false)); // enable / disable mouse or touch interaction.

//	scrollView->setDoubleTapZoom(true); // enable double tap zoom.
//	scrollView->setDoubleTapZoomIncrement(1.0); // the increment value of zoom on double tap, between 0 and 1.
//	scrollView->setDoubleTapZoomIncrementTimeInSec(0.3); // the time amount of time for zoom increment.
//	scrollView->setDoubleTapRegistrationTimeInSec(0.25); // the time threshold between taps for double tap event to register.
//	scrollView->setDoubleTapRegistrationDistanceInPixels(20); // the distance threshold between taps for double tap event to register.

	scrollView->setup(); // setup must always be called at the end of scroll view config.
}

void ScrollViewSampleApp::update() {

	scrollView->update();
}

void ScrollViewSampleApp::draw() {

	gl::clear(Color(0.5, 0.5, 0.5));

	// ScrollView returns a matrix to do any transformations manually,
	// otherwise drawing things between begin() and end() methods will also do the trick.

	scrollView->begin();
	grid.draw();
	scrollView->end();

    gl::ScopedColor color(Color(0, 0, 0));
	gl::VertBatch vb( GL_TRIANGLE_STRIP);
    vb.vertex(0, 0);
    vb.vertex(windowRect.x1, windowRect.y1);
    vb.vertex(getWindowWidth(), 0);
    vb.vertex(windowRect.x2, windowRect.y1);
    vb.vertex(getWindowWidth(), getWindowHeight());
    vb.vertex(windowRect.x2, windowRect.y2);
    vb.vertex(0, getWindowHeight());
    vb.vertex(windowRect.x1, windowRect.y2);
    vb.vertex(0, 0);
    vb.vertex(windowRect.x1, windowRect.y1);
	vb.draw();
    
}

void ScrollViewSampleApp::cleanup() {
//	scrollView->setUserInteraction(false); // always remember to disable user interaction when killing the scrollview class.
}

void ScrollViewSampleApp::mouseMove( MouseEvent event ) {
    if(bUserInteractionManual == true) {
        scrollView->pointMoved(event.getX(), event.getY(), 0);
    }
}

void ScrollViewSampleApp::mouseDown( MouseEvent event ) {
    if(bUserInteractionManual == true) {
        scrollView->pointPressed(event.getX(), event.getY(), 0);
    }
}

void ScrollViewSampleApp::mouseDrag( MouseEvent event ) {
    if(bUserInteractionManual == true) {
        scrollView->pointDragged(event.getX(), event.getY(), 0);
    }
}

void ScrollViewSampleApp::mouseUp( MouseEvent event ) {
    if(bUserInteractionManual == true) {
        scrollView->pointReleased(event.getX(), event.getY(), 0);
    }
}

CINDER_APP( ScrollViewSampleApp, RendererGl, &prepareSettings )
