������͂ȂɁH

GDI ��p�����_�u���o�b�t�@�����O���s�� DrawDevice �ł��B
DrawDevice �̃x�[�X�N���X�񋟂Ǝ����̃T���v�������˂Ă��܂��B
ClipRect �̏������s���Ă��Ȃ��̂ŁA�v���C�}���[���C���[���E�B���h�E�T�C�Y���傫���ꍇ�Ȃ��Y��ɃN���b�s���O����Ȃ��Ȃǖ�肪����Ǝv���܂��B
�Q�[���p�ł͂Ȃ��A�ǂ��炩�Ƃ����ƃc�[���p�ł����AVista �ȍ~�ʏ�̕`��� DirectX �ōs���Ă��錻�݂̊��ł͗]��Ӗ��͂Ȃ���������܂���B



���g����

1. Window �� drawDevice �ɑ΂��Ďw��\�ł�

���z�R�[�h�ŏ����ƃC���^�[�t�F�C�X�͈ȉ��̂悤�ɂȂ��Ă��܂��B
class GDIDrawDevice {
	property interface // read only
};

�ȉ��̂悤�ɂ��Ďg�p���܂��B
-------------------------------------------
Plugins.link("gdidrawdevice.dll");
class MyWindow extends Window {
  var base;
  function MyWindow(width,height) {
    super.Window();
    setInnerSize(width, height);
    // drawdevice �������ւ�
    drawDevice = new GDIDrawDevice();
     // �v���C�}�����C������
    base = new Layer(this,null);
    base.setSize(width,height);
    add(base);
  }
};
-------------------------------------------



�����C�Z���X

���̃v���O�C���̃��C�Z���X�͋g���g���{�̂ɏ���(�C��BSD)���Ă��������B

