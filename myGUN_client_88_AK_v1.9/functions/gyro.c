ISR(TIMER0_COMPB_vect) { //обработчик каждой 4ой миллисекунды
//	uint8_t rx,ry,rz,dx,dy,dz;
//	wdt_reset(); 				//погладим собачку
//	sei();

	l3g4200d_getrawdata(&gxraw, &gyraw, &gzraw);
	gx=trunc((gxraw * 0.004)*100)/100;
//	gy=trunc((gyraw * 0.016)*100)/100;
	gz=trunc((gzraw * 0.004)*100)/100;
	if (fabs(gx)>0.1f) { PositionX +=gx; }
//	if (fabs(gy)>0.1f) { PositionY +=gy; }
	if (fabs(gz)>0.1f) { PositionZ +=gz; }
	PositionX2=PositionX*100/2370;
//	PositionY2=PositionY*100/2370;
	PositionZ2=PositionZ*100/2370;
	angleX=floor(360/10*PositionX2)/10;
//	angleY=floor(360/10*PositionY2)/10;
	angleZ=floor(360/10*PositionZ2)/10;

	//Это заполнение по углу завала
	if (abs(angleX)>80) {
		DataToRF[4]=80;		//это предельное хначение угла завала
		DataToRF[5]=(DataToRF[5] & 0xF0);
		}
		else {
			DataToRF[4]=trunc(fabs(angleX));	//забираем угол до 80
			DataToRF[5]=(DataToRF[5] & 0xF0) | ((abs(angleX*10)) - (DataToRF[4] & 0x7F)*10);
		}
	if (angleX>=0) DataToRF[4] &= ~(0x80);
		else  DataToRF[4] |= (0x80);

/*
	//Это заполнение по углу наклона
	if (abs(angleZ)>80) {
		DataToRF[6]=80;		//это предельное хначение угла завала
		DataToRF[7]=(DataToRF[7] & 0xF0);
		}
		else {
			DataToRF[6]=trunc(fabs(angleZ));	//забираем угол до 80
			DataToRF[7]=(DataToRF[7] & 0xF0) | ((abs(angleY*10)) - (DataToRF[6] & 0x7F)*10);
		}
	if (angleZ>=0) DataToRF[6] &= ~(0x80);
		else  DataToRF[6] |= (0x80);
*/
	TCNT0 = 0;					//предустановка счетчика таймера
//	wdt_reset(); 				//погладим собачку
}
