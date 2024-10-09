#pragma execution_character_set("utf-8")//解决中文乱码
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QImage>
#include <QRegularExpression>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <cmath>
#include <QInputDialog>
#include <QGuiApplication>
#include <QScreen>
#include <QtCore/QCoreApplication>
#include <QSettings>
#include <opencv2/opencv.hpp>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSettings *settings;

private slots:
    void setThreshold();
    void openCenterImage();
    void markCenterImageRegions();
    void openJoint1Image();
    void markJoint1ImageRegions();
    void openJoint2Image();
    void markJoint2ImageRegions();
    void CenterCalculate();
    void Joint1Calculate();
    void Joint2Calculate();
    void saveResultTextToFile();
    void saveMarkedImageToFile();

private:
    QLabel* m_centerResultLabel;// 中心区域判断结果显示区域
    QLabel* m_joint1ResultLabel;// 拼接区域1判断结果显示区域
    QLabel* m_joint2ResultLabel;// 拼接区域2判断结果显示区域
    QDialog* m_thresholdDialog; // 用于显示阈值设置对话框
    double m_X1,m_Y1,m_W1,m_H1;// 图1目标区域
    double m_X2,m_Y2,m_W2,m_H2;// 图2目标区域
    double m_X3,m_Y3,m_W3,m_H3;// 图3目标区域
    double m_X4,m_Y4,m_W4,m_H4;// 图4目标区域
    double m_X5,m_Y5,m_W5,m_H5;// 图5目标区域
    double m_X6,m_Y6,m_W6,m_H6;// 图6目标区域
    QImage m_image1; // 原始图像1
    QImage m_image2; // 原始图像2
    QImage m_image3; // 原始图像3
    QImage m_image4; // 原始图像4
    QImage m_image5; // 原始图像5
    QImage m_image6; // 原始图像6
    QImage m_image1Copy; // 用于原始图像1的标记图像
    QImage m_image2Copy; // 用于原始图像2的标记图像
    QImage m_image3Copy; // 用于原始图像3的标记图像
    QImage m_image4Copy; // 用于原始图像4的标记图像
    QImage m_image5Copy; // 用于原始图像5的标记图像
    QImage m_image6Copy; // 用于原始图像6的标记图像
    QLabel* m_centerLabel1; // 中心区域图像对比显示区域
    QLabel* m_centerLabel2; // 中心区域图像对比显示区域
    QLabel* m_joint1Label1; // 拼接区域1图像对比显示区域
    QLabel* m_joint1Label2; // 拼接区域1图像对比显示区域
    QLabel* m_joint2Label1; // 拼接区域2图像对比显示区域
    QLabel* m_joint2Label2; // 拼接区域2图像对比显示区域
    QLabel* m_centerBrightnessResultLabel; // 中心区域亮度测试数据结果显示区域
    QLabel* m_joint1BrightnessResultLabel; // 拼接区域1亮度测试数据结果显示区域
    QLabel* m_joint2BrightnessResultLabel; // 拼接区域2亮度测试数据结果显示区域
    QLabel* m_centerColorResultLabel; // 中心区域色彩测试数据结果显示区域
    QLabel* m_joint1ColorResultLabel; // 拼接区域1色彩测试数据结果显示区域
    QLabel* m_joint2ColorResultLabel; // 拼接区域2色彩测试数据结果显示区域
    double m_centerbrightness[2]; // 中心区域平均亮度计算结果
    double m_joint1brightness[2]; // 拼接区域1平均亮度计算结果
    double m_joint2brightness[2]; // 拼接区域2平均亮度计算结果
    cv::Scalar centerBgr1;// 中心区域(左)平均RGB计算结果
    cv::Scalar centerBgr2;// 中心区域(右)平均RGB计算结果
    cv::Scalar joint1Bgr1;// 拼接区域1区域(左)平均RGB计算结果
    cv::Scalar joint1Bgr2;// 拼接区域1(右)平均RGB计算结果
    cv::Scalar joint2Bgr1;// 拼接区域2(左)平均RGB计算结果
    cv::Scalar joint2Bgr2;// 拼接区域2(右)平均RGB计算结果
    double m_centerRG[2]; // 中心区域R/G计算结果
    double m_joint1RG[2]; // 拼接区域1R/G计算结果
    double m_joint2RG[2]; // 拼接区域2R/G计算结果
    double m_centerBG[2]; // 中心区域B/G计算结果
    double m_joint1BG[2]; // 拼接区域1B/G计算结果
    double m_joint2BG[2]; // 拼接区域2B/G计算结果
    double m_centerBrightnessLimit = 50;// 中心区域亮度绝对差上限
    double m_joint1BrightnessLimit = 50;// 拼接区域1亮度绝对差上限
    double m_joint2BrightnessLimit = 50;// 拼接区域2亮度绝对差上限
    double m_centerRGLimit = 1;// 中心区域R/G绝对差上限
    double m_joint1RGLimit = 1;// 拼接区域1R/G绝对差上限
    double m_joint2RGLimit = 1;// 拼接区域2R/G绝对差上限
    double m_centerBGLimit = 1;// 中心区域B/G绝对差上限
    double m_joint1BGLimit = 1;// 拼接区域1B/G绝对差上限
    double m_joint2BGLimit = 1;// 拼接区域2B/G绝对差上限
    bool CenterbrightnessPass = true;// 中心区域亮度绝对差判定
    bool Joint1brightnessPass = true;// 拼接区域1亮度绝对差判定
    bool Joint2brightnessPass = true;// 拼接区域2亮度绝对差判定
    bool CenterRGPass = true;// 中心区域R/G绝对差判定
    bool Joint1RGPass = true;// 拼接区域1R/G绝对差判定
    bool Joint2RGPass = true;// 拼接区域2R/G绝对差判定
    bool CenterBGPass = true;// 中心区域B/G绝对差判定
    bool Joint1BGPass = true;// 拼接区域1B/G绝对差判定
    bool Joint2BGPass = true;// 拼接区域2B/G绝对差判定

    void calculateCenterBrightness(); // 计算并判断中心区域亮度
    void calculateCenterColor(); // 计算并判断中心区域色彩
    void calculateJoint1Brightness(); // 计算并判拼接区域1亮度
    void calculateJoint1Color(); // 计算并判断拼接区域1色彩
    void calculateJoint2Brightness(); // 计算并判拼接区域2亮度
    void calculateJoint2Color(); // 计算并判断拼接区域2色彩
};

#endif // MAINWINDOW_H
