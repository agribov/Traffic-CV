#ifndef QTCVVIEWER
#define QTCVVIEWER

/*********************************************************************************/
// This file is from the following tutorial: 
// http://www.robot-home.it/blog/en/software/tutorial-opencv-qt-opengl-widget-per-visualizzare-immagini-da-opencv-in-una-gui-con-qt/
/*********************************************************************************/

#include <QOpenGLWidget>
#include <QOpenGLFunctions_2_0>
#include <opencv2/core/core.hpp>

class CQtOpenCVViewerGl : public QOpenGLWidget, protected QOpenGLFunctions_2_0
{
	Q_OBJECT
public:
	explicit CQtOpenCVViewerGl(QWidget *parent = 0);

signals:
	void    imageSizeChanged(int outW, int outH); /// Used to resize the image outside the widget

	public slots:
	bool    showImage(const cv::Mat& image); /// Used to set the image to be viewed

protected:
	void 	initializeGL(); /// OpenGL initialization
	void 	paintGL(); /// OpenGL Rendering
	void 	resizeGL(int width, int height);        /// Widget Resize Event

	void        updateScene();
	void        renderImage();

private:

	QImage      mRenderQtImg;           /// Qt image to be rendered
	QImage      mResizedImg;
	cv::Mat     mOrigImage;             /// original OpenCV image to be shown

	QColor      mBgColor;		/// Background color

	float       mImgRatio;             /// height/width ratio

	int mRenderWidth;
	int mRenderHeight;
	int mRenderPosX;
	int mRenderPosY;

	void recalculatePosition();
};

#endif // QTCVVIEWER