Disolvente = input('datos del disolvente en %: ');
Soluto = input('datos del soluto en %: ');
Diagonal = [0 100;100,0];
Portador = input('datos del portador en %: ');
%Puntos de la línea de reparto
Refinado = input('Refinado: Disolvente,Soluto,Portador: ');
Extracto = input('Extracto: Disolvente,Soluto,Portador: ');
%Coordenadas extremos de las líneas de reparto
x = input('coordenadas eje x: ');
y = input('coordenadas eje y: ');
m = input('valores de m: ');
n = input('valores de n: ');
i=1;j=2;
figure
plot(Disolvente,Soluto,'black-',Diagonal(:,1),Diagonal(:,2),'b--')
hold on
while i<=length(x)
    while j<=length(y)
        plot(x(i:j),y(i:j))
        hold on
        i = i+2;
        j = j+2;
    end
end
DATOS = input('Introduce los datos: ');
DATOS(3,4) = DATOS(1,4)+DATOS(3,4);
if DATOS(3,1) == 0
    DATOS(3,1) = (DATOS(1,1)*DATOS(1,4)+DATOS(2,1)*DATOS(2,4))/datos(3,4);
end
if DATOS(3,2) == 0
    DATOS(3,2) = (DATOS(1,2)*DATOS(1,4)+DATOS(2,2)*DATOS(2,4))/datos(3,4);
end
if DATOS(3,3) == 0
    DATOS(3,3) = 100-DATOS(3,1)-DATOS(3,2);
end
 %Recta F-S
 FS = DATOS(1:2,1:2);
 % Punto de mezcla
 Mezcla = DATOS(3,1:2);
