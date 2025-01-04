#include <QApplication>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QStringList>
#include <QSysInfo>
#include <iostream>
#include "display_manager.h"  // Platform-specific display resolution header

// Function to update the resolution dropdown in Qt
void updateResolutionList(QComboBox* comboBox) {
    std::vector<ScreenResolution> resolutions = getResolutionsForPlatform();
    QStringList resolutionList;

    for (const auto& res : resolutions) {
        resolutionList << QString::number(res.width) + "x" + QString::number(res.height);
    }

    comboBox->addItems(resolutionList);
}

// Function to handle the resolution change in Qt
void onResolutionSelected(QComboBox* comboBox) {
    QString selectedResolution = comboBox->currentText();
    QStringList parts = selectedResolution.split('x');
    if (parts.size() == 2) {
        int width = parts[0].toInt();
        int height = parts[1].toInt();
        setResolutionForPlatform(width, height);
    }
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("ResoManager");

    QComboBox* comboBox = new QComboBox();
    updateResolutionList(comboBox);

    QPushButton* applyButton = new QPushButton("Apply Resolution");
    QObject::connect(applyButton, &QPushButton::clicked, [comboBox]() {
        onResolutionSelected(comboBox);
    });

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(comboBox);
    layout->addWidget(applyButton);
    window.setLayout(layout);

    window.show();

    return app.exec();
}
