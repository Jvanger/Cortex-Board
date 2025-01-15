#include "lsm6dsm_reg.h"
#include "main.h"


// Sensor interface declarations
stmdev_ctx_t dev_ctx;  
TaskHandle_t Task_Handle_IMU;

// Raw acceleration data
int16_t data_raw[3];

//function declarations 
void task_IMU(void *pvParameters);
void task_IMU_init(void);

// Tilt threshold (deg)
#define TILT_THRESHOLD 15 
static int32_t platform_write(void *handle, uint8_t reg, const uint8_t *bufp,
                              uint16_t len);
static int32_t platform_read(void *handle, uint8_t reg, uint8_t *bufp,
                             uint16_t len);

extern uint16_t x_tilt; 
extern uint16_t y_tilt;
extern uint16_t z_tilt;

void task_IMU(void *pvParameters) {

  // Initialize sensor interface
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;
  
  // Set full scale to 2g
  lsm6dsm_xl_full_scale_set(&dev_ctx, LSM6DSM_2g);

  // Set ODR to 104 Hz
  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_104Hz);
  
  while(1) {

    // Read raw acceleration  
    lsm6dsm_acceleration_raw_get(&dev_ctx, data_raw);

    // Calculate tilt angle in X Y Z axes
     x_tilt = abs(atan2(data_raw[1], data_raw[2]) * 180/M_PI); 
     y_tilt = abs(atan2(data_raw[0], data_raw[2]) * 180/M_PI);
     z_tilt = abs(atan2(data_raw[0], data_raw[1]) * 180/M_PI);

    // Print tilt angles    
    printf("Tilt X: %d Y: %d Z: %d\n", x_tilt, y_tilt, z_tilt);

    // Check tilt threshold on any axis
    if (x_tilt > TILT_THRESHOLD || y_tilt > TILT_THRESHOLD || z_tilt > TILT_THRESHOLD) {
      printf("Tilt detected!\n"); 
    }
    
    delay(100);
  }
}

void task_IMU_init(void) {
  xTaskCreate(task_IMU, "IMU", 4096, NULL, 1, &Task_Handle_IMU);
}

