#ifndef CAMERA_H
#define CAMERA_H

#include "M5CoreS3.h"
#include "SD.h"
#include "esp_camera.h"

void initCamera() {
  if (!CoreS3.Camera.begin()) {
    Serial.println("Camera Init Failed");
  }
  CoreS3.Camera.sensor->set_framesize(CoreS3.Camera.sensor, FRAMESIZE_QVGA);
}

void shot() {
  if (CoreS3.Camera.get()) {
    uint8_t *out_jpg = NULL;
    size_t out_jpg_len = 0;
    frame2jpg(CoreS3.Camera.fb, 255, &out_jpg, &out_jpg_len);
    char filename[32];
    sprintf(filename, "/picture_%ld.jpg", millis());
    File file = SD.open(filename, FILE_WRITE);
    if (file) {
      file.write(out_jpg, out_jpg_len);
      Serial.println("Saved: " + String(filename));
      file.close();
    } else {
      Serial.println("Failed to open file for writing");
    }
    free(out_jpg);
    CoreS3.Camera.free();
  }
}

#endif
