/*Runge-Kutta*/

#for (T, 1, time_n, time_step)

#local a_t1 = w1;
#local a_t2 = w2;
#local a_w1 = (-grav*(2*m1+m2)*sin(theta1)-m2*grav*sin(theta1-2*theta2)-2*sin(theta1-theta2)*m2*(w2*w2*length2+w1*w1*length1*cos(theta1-theta2)))/(length1*(2*m1+m2-m2*cos(2*theta1-2*theta2)));
#local a_w2 = (2*sin(theta1-theta2)*(w1*w1*length1*(m1+m2)+grav*(m1+m2)*cos(theta1)+w2*w2*length2*m2*cos(theta1-theta2)))/(length2*(2*m1+m2-m2*cos(2*theta1-2*theta2)));

#local b_t1 = w1 + (time_step/2.0) * a_w1;
#local b_t2 = w2 + (time_step/2.0) * a_w2;
#local b_w1 = (-grav*(2*m1+m2)*sin(theta1 + (time_step/2.0) * a_t1)-m2*grav*sin((theta1 + (time_step/2.0) * a_t1)-2*(theta2 + (time_step/2.0) * a_t2))-2*sin((theta1 + (time_step/2.0) * a_t1)-(theta2 + (time_step/2.0) * a_t2))*m2*((w2 + (time_step/2.0) * a_w2)*(w2 + (time_step/2.0) * a_w2)*length2+(w1 + (time_step/2.0) * a_w1)*(w1 + (time_step/2.0) * a_w1)*length1*cos((theta1 + (time_step/2.0) * a_t1)-(theta2 + (time_step/2.0) * a_t2))))/(length1*(2*m1+m2-m2*cos(2*(theta1 + (time_step/2.0) * a_t1)-2*(theta2 + (time_step/2.0) * a_t2))));
#local b_w2 = (2*sin((theta1 + (time_step/2.0) * a_t1)-(theta2 + (time_step/2.0) * a_t2))*((w1 + (time_step/2.0) * a_w1)*(w1 + (time_step/2.0) * a_w1)*length1*(m1+m2)+grav*(m1+m2)*cos(theta1 + (time_step/2.0) * a_t1)+(w2 + (time_step/2.0) * a_w2)*(w2 + (time_step/2.0) * a_w2)*length2*m2*cos((theta1 + (time_step/2.0) * a_t1)-(theta2 + (time_step/2.0) * a_t2)))) / (length2*(2*m1+m2-m2*cos(2*(theta1 + (time_step/2.0) * a_t1)-2*(theta2 + (time_step/2.0)*a_t2))));

#local c_t1 = w1 + (time_step/2.0) * b_w1;
#local c_t2 = w2 + (time_step/2.0) * b_w2;
#local c_w1 = (-grav*(2*m1+m2)*sin(theta1 + (time_step/2.0) * b_t1)-m2*grav*sin((theta1 + (time_step/2.0) * b_t1)-2*(theta2 + (time_step/2.0) * b_t2))-2*sin((theta1 + (time_step/2.0) * b_t1)-(theta2 + (time_step/2.0) * b_t2))*m2*((w2 + (time_step/2.0) * b_w2)*(w2 + (time_step/2.0) * b_w2)*length2+(w1 + (time_step/2.0) * b_w1)*(w1 + (time_step/2.0) * b_w1)*length1*cos((theta1 + (time_step/2.0) * b_t1)-(theta2 + (time_step/2.0) * b_t2))))/(length1*(2*m1+m2-m2*cos(2*(theta1 + (time_step/2.0) * b_t1)-2*(theta2 + (time_step/2.0) * b_t2))));
#local c_w2 = (2*sin((theta1 + (time_step/2.0) * b_t1)-(theta2 + (time_step/2.0) * b_t2))*((w1 + (time_step/2.0) * b_w1)*(w1 + (time_step/2.0) * b_w1)*length1*(m1+m2)+grav*(m1+m2)*cos(theta1 + (time_step/2.0) * b_t1)+(w2 + (time_step/2.0) * b_w2)*(w2 + (time_step/2.0) * b_w2)*length2*m2*cos((theta1 + (time_step/2.0) * b_t1)-(theta2 + (time_step/2.0) * b_t2))))/(length2*(2*m1+m2-m2*cos(2*(theta1 + (time_step/2.0) * b_t1)-2*(theta2 + (time_step/2.0)*b_t2))));

#local d_t1 = w1 + (time_step) * c_w1;
#local d_t2 = w2 + (time_step) * c_w2;
#local d_w1 = (-grav*(2*m1+m2)*sin(theta1 + (time_step) * c_t1)-m2*grav*sin((theta1 + (time_step) * c_t1)-2*(theta2 + (time_step) * c_t2))-2*sin((theta1 + (time_step) * c_t1)-(theta2 + (time_step) * c_t2))*m2*((w2 + (time_step) * c_w2)*(w2 + (time_step) * c_w2)*length2+(w1 + (time_step) * c_w1)*(w1 + (time_step) * c_w1)*length1*cos((theta1 + (time_step) * c_t1)-(theta2 + (time_step) * c_t2))))/(length1*(2*m1+m2-m2*cos(2*(theta1 + (time_step) * c_t1)-2*(theta2 + (time_step) * c_t2))));
#local d_w2 = (2*sin((theta1 + (time_step) * c_t1)-(theta2 + (time_step) * c_t2))*((w1 + (time_step) * c_w1)*(w1 + (time_step) * c_w1)*length1*(m1+m2)+grav*(m1+m2)*cos(theta1 + (time_step) * c_t1)+(w2 + (time_step) * c_w2)*(w2 + (time_step) * c_w2)*length2*m2*cos((theta1 + (time_step) * c_t1)-(theta2 + (time_step) * c_t2))))/(length2*(2*m1+m2-m2*cos(2*(theta1 + (time_step) * c_t1)-2*(theta2 + (time_step)*c_t2))));

#declare theta1 = theta1 + time_step * (a_t1 + 2*b_t1 + 2*c_t1 + d_t1)/6.0;
#declare theta2 = theta2 + time_step * (a_t2 + 2*b_t2 + 2*c_t2 + d_t2)/6.0;
#declare w1 = w1 + time_step * (a_w1 + 2*b_w1 + 2*c_w1 + d_w1)/6.0;
#declare w2 = w2 + time_step * (a_w2 + 2*b_w2 + 2*c_w2 + d_w2)/6.0;

#end
