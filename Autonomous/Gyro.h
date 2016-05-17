#define		GYRO_MAX_OFFSET		60
#define		GYRO_MAX			3600
//Used By Roger Pan
int gyro_last = 0;

int gyro_value = 0;

// + CCW : - CW
int Gyro_Get () {
	return gyro_value;
}

void Gyro_Reset () {
	gyro_value = 0;
	gyro_last = 0;
	SensorValue[Gyro] = 0;
}

// void Gyro_Set (int value) {
// 	gyro_value = value;
// }


void Gyro_Refresh () {
	int gyro_current = SensorValue[Gyro];
	int gyro_offset = gyro_current - gyro_last;

	if (abs(gyro_offset) > GYRO_MAX_OFFSET) {
		if (gyro_offset > 0) {
			gyro_offset -= GYRO_MAX;
		} else if (gyro_offset < 0) {
			gyro_offset += GYRO_MAX;
		}
	}

	// if (gyro_offset != 0) {
	// 	writeDebugStream(
	// 		"Cur : %d\tLast : %d\tOffset : %d\nValue : %d\n",
	// 		gyro_current,
	// 		gyro_last,
	// 		gyro_offset,
	// 		gyro_value);
	// }

	gyro_value += gyro_offset;
	gyro_last = gyro_current;
}