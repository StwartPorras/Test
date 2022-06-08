import math
def  caudal(Z,L,D,rugosidad,viscosidad,densidad):
    Q = 0.1
    area = (math.pi)*pow(D,2)/4
    vel = Q/area
    Re = densidad*vel*D/viscosidad
    A = pow(2.457*math.log(1/(pow(7/Re,0.9)+0.27*rugosidad/D)),16)
    B = pow(37.530/Re,16)
    f = 2*pow(pow(8/Re,12)+1/(pow(A+B,1.5)),1/12)
    beta = 32*f*L/(pow(D,5)*pow(math.pi,2)*9.81)
    Qn = math.sqrt(Z/beta)
    Diff = Q-Qn
    while Diff != 0:
        Q = Q-Diff
        vel = Q/D
        Re = densidad*vel*D/viscosidad
        A = pow(2.457*math.log(1/(pow(7/Re,0.9)+0.27*rugosidad/D)),16)
        B = pow(37.530/Re,16)
        f = 2*pow(pow(8/Re,12)+1/(pow(A+B,1.5)),1/12)
        beta = 32*f*L/(pow(D,5)*pow(math.pi,2)*9.81)
        Qn = math.sqrt(Z/beta)
        Diff = Q-Qn
    return Diff,Qn
print(caudal(10,100,0.05,0.0015,0.001,1000))
