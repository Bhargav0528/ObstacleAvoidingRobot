#include <Servo.h>
#define SIZE 10

void merge();
void mergeSort();
void getConsistent();


int triggerPin = 10;
int echoPin = 11;

int RightDC = 6;
int LeftDC = 5;

Servo myservo;  // create servo object to control a servo



void setup() {
  // put your setup code here, to run once:
  myservo.attach(3);
  myservo.write(68);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(RightDC, OUTPUT);
  pinMode(LeftDC, OUTPUT);
  Serial.begin(38400);
}


void loop() {
  // put your main code here, to run repeatedly:
  int i, a[SIZE];
  int duration;
  int distance, distance1, distance2, right = 0, left = 0;

  
  for (i = 0; i <= 9; i++)
  {

    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);
    
    
    

    duration = pulseIn(echoPin, HIGH); //a special function for listening and waiting for the wave
    distance2 = (duration / 2) / 29.1; //transforming the number to cm(if you want inches, you have to change the 29.1 with a suitable numbe

    a[i] = distance2;
  }

  distance = getConsistent(a);
  Serial.println(distance);

  if (distance < 35 )
  {
    Serial.println("********* Obstacle ************ ");
    digitalWrite(RightDC, LOW);
    digitalWrite(LeftDC, LOW);
    delay(1000);


    myservo.write(0);
    delay(1000);
    right = 0.0;
    for (i = 0; i < 10; i++)
    {
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);
      duration = pulseIn(echoPin, HIGH); //a special function for listening and waiting for the wave
      distance1 = (duration / 2) / 29.1;

      a[i] = distance1;
      delay(100);
    }
    //transforming the number to cm(if you want inches, you have to change the 29.1 with a suitable number


    right = getConsistent(a);
    Serial.print("Right");
    Serial.println(right);




    myservo.write(134);
    delay(1000);
    left = 0.0;
    for (i = 0; i < 10; i++)
    {
      digitalWrite(triggerPin, LOW);
      delayMicroseconds(2);
      digitalWrite(triggerPin, HIGH);
      delayMicroseconds(10);
      digitalWrite(triggerPin, LOW);
      duration = pulseIn(echoPin, HIGH); //a special function for listening and waiting for the wave
      distance1 = (duration / 2) / 29.1; //transforming the number to cm(if you want inches, you have to change the 29.1 with a suitable number

      a[i] =  distance1;
      delay(100);
    }

    left = getConsistent(a);

    Serial.print("left");
    Serial.println(left);


    myservo.write(68);

    if (distance < 35)
    {
      if (right > left)
      {
        digitalWrite(LeftDC, HIGH);
        delay(2650);
        digitalWrite(LeftDC, LOW);
        delay(2000);
      }
      else
      {
        digitalWrite(RightDC, HIGH);
        delay(2650);
        digitalWrite(RightDC, LOW);
        delay(1000);
      }
    }
  }
  else
  {
    Serial.println("*********In else*********");
    digitalWrite(RightDC, HIGH);
    digitalWrite(LeftDC, HIGH);
    delay(1000);
  }
}



void merge(int arr[], int l, int m, int r)
{
  int i, j, k;
  int n1 = m - l + 1;
  int n2 =  r - m;

  /* create temp arrays */
  int L[n1], R[n2];

  /* Copy data to temp arrays L[] and R[] */
  for (i = 0; i < n1; i++)
    L[i] = arr[l + i];
  for (j = 0; j < n2; j++)
    R[j] = arr[m + 1 + j];

  /* Merge the temp arrays back into arr[l..r]*/
  i = 0; // Initial index of first subarray
  j = 0; // Initial index of second subarray
  k = l; // Initial index of merged subarray
  while (i < n1 && j < n2)
  {
    if (L[i] <= R[j])
    {
      arr[k] = L[i];
      i++;
    }
    else
    {
      arr[k] = R[j];
      j++;
    }
    k++;
  }

  /* Copy the remaining elements of L[], if there
     are any */
  while (i < n1)
  {
    arr[k] = L[i];
    i++;
    k++;
  }

  /* Copy the remaining elements of R[], if there
     are any */
  while (j < n2)
  {
    arr[k] = R[j];
    j++;
    k++;
  }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
  if (l < r)
  {
    // Same as (l+r)/2, but avoids overflow for
    // large l and h
    int m = l + (r - l) / 2;

    // Sort first and second halves
    mergeSort(arr, l, m);
    mergeSort(arr, m + 1, r);

    merge(arr, l, m, r);
  }
}


int getConsistent(int a[])
{
  int maxi[SIZE] = {0}, count[SIZE]= {0};
  int i, j, temp, index = 0, k = 0, lastno = 0, l = 0, big = 0, b=0;




    
  mergeSort(a, 0, SIZE - 1);

    for (i = 0; i < SIZE; i++)
    Serial.println(a[i]);

  for (; i < SIZE; i++)
  {
    i = index;
    temp = a[i];
    b = 0;
    for (j = 0; j < SIZE; j++)
    {
      if ( a[j] < temp + 10)
      {
        b += 1;
        index = j + 1;
        lastno = a[j];

      }
    }

    count[k++] = b;
    maxi[b] = lastno;

  }
  for (i = 0; i < k - 1; i++)
    if (count[i] >= big)
      big = count[i];

  

  return( maxi[big] );
}

