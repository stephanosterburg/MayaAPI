""" Intro Maya QT """
from PyQt4 import QtCore, QtGui, uic
import maya.cmds as cmds

UI_FILE = "qt_basic.ui"
UiMainWindow, QtBaseClass = uic.loadUiType(UI_FILE)


class CreateUI(QtGui.QMainWindow, UiMainWindow):
    """
    create ui
    """
    def __init__(self):
        """
        Initialize the window.
        """
        QtGui.QMainWindow.__init__(self)
        UiMainWindow.__init__(self)
        self.setupUi(self)

        self.establish_connections()
        self.update_description()

    def establish_connections(self):
        """
        connect ui fields to functions
        """
        self.connect(self.shape_type_cb,
                     QtCore.SIGNAL("currentIndexChanged(int)"),
                     self.update_description)
        self.connect(self.name_le, QtCore.SIGNAL("textChanged(const QString&)"),
                     self.update_description)
        self.connect(self.make_button, QtCore.SIGNAL("clicked()"),
                     self.make_shape)

    def update_description(self):
        """
        Update the descriptive label. This method gets called when either the
        shapeTypeCB or nameLE get modified by the user.
        """
        description = 'Make a %s named "%s"' % \
                      (self.shape_type_cb.currentText(), self.name_le.text())
        self.desc_label.setText(description)
        self.name_le.setText("new" + self.shape_type_cb.currentText() + "Shape")

    def make_shape(self):
        """
        Make the shape. This gets called when the user clicks on the
        "Make Shape" makeButton.
        """
        obj_type = self.shape_type_cb.currentText()

        if obj_type == 'Sphere':
            cmd = cmds.polySphere
        elif obj_type == 'Cube':
            cmd = cmds.polyCube
        else:
            cmd = cmds.polyCylinder

        cmd(name=str(self.name_le.text()))


if __name__ == "__main__":
    dialog = CreateUI()
    dialog.show()
