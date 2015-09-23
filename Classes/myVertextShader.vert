attribute vec4 a_position;
attribute vec4 a_color; //定义了两个属性变量 

varying vec4 v_fragmentColor; //定义一个易变变量

void main()
{
    gl_Position = CC_MVPMatrix * a_position;
    v_fragmentColor = a_color;
}
