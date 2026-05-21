#include <Arduino.h>
#include "svm_model.h"
#include "scaler1.h"
#include "test_images.h"

void scale_input(float *x) {
  for(int i=0;i<NUM_FEATURES;i++) {
    x[i] = (x[i] - mean[i]) / scale[i];
  }
}

int predict(float *x) {
  int best_class = 0;
  float max_score = -INFINITY;

  for(int c=0;c<NUM_CLASSES;c++) {

    float score = bias[c];

    for(int i=0;i<NUM_FEATURES;i++) {
      score += weights[c][i] * x[i];
    }

    if(score > max_score){
      max_score = score;
      best_class = c;
    }
  }

  return best_class;
}

void setup() {

  Serial.begin(115200);
  delay(2000);

  Serial.println("Edge AI on ESP32 Started");

  for(int i=0;i<NUM_TEST_IMAGES;i++) {

    scale_input(test_images[i]);

    int predicted = predict(test_images[i]);
    int actual = test_labels[i];

    Serial.print("Image ");
    Serial.print(i);
    Serial.print(" Predicted=");
    Serial.print(predicted);
    Serial.print(" Actual=");
    Serial.println(actual);
  }
}

void loop() {
}