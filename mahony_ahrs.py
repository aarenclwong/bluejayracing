import bz2
import math
import numpy as np

DEFAULT_SAMPLE_FREQ = 512.0 # sample freq in Hz
twoKpDef = 2.0 * 0.5        # 2 * proportional gain
twoKiDef = 2.0 * 0.0        # 2 * integral gain

class Mahony:
    def __init__(self, sample_freq=DEFAULT_SAMPLE_FREQ):
        self.twoKp = twoKpDef
        self.twoKi = twoKiDef
        self.q0 = 1.0
        self.q1 = 0.0
        self.q2 = 0.0
        self.q3 = 0.0
        self.integralFBx = 0.0
        self.integralFBx = 0.0
        self.integralBz = 0.0
        self.anglesComputed = False
        self.invSampleFreq = 1.0/sample_freq
        
        self.roll = 0
        self.pitch = 0
        self.yaw = 0

    def getRoll(self):
        if not self.anglesComputed:
            self.computeAngles()
        return self.roll * 57.29578
        
    def getPitch(self):
        if not self.anglesComputed:
            self.computeAngles()
        return self.pitch * 57.29578

    def getYaw(self):
        if not self.anglesComputed:
            self.computeAngles()
        return self.yaw * 57.29578

    # g's should be in rad/sec
    def update(self, gx, gy, gz, ax, ay, az, mx, my, mz):
        recipNorm = 0
        q0q1 = q0q1 = q0q1 = q0q3 = q1q1 = q1q2 = q1q3 = q2q2 = q2q3 = q3q3 = 0.0
        hx = hy = bx = bz = 0.0
        halfvx = halfvy = halfvz = halfwx = halfwy = halfwz = 0.0
        halfex = halfey = halfez = 0
        qa = qb = qc = 0

        if mx == 0 and my == 0 and mz == 0:
            self.updateIMU(gx, gy, ax, ay, az)
            return
        
        # De-Morgan's law
        if ax != 0.0 or ay != 0.0 or az != 0.0:

            # Normalize accelerometer measurement
            recipNorm = 1/math.sqrt(ax**2 + ay**2 + az**2)
            ax *= recipNorm
            ay *= recipNorm
            az *= recipNorm

            # Normalize magnetometer measurement
            recipNorm = 1/math.sqrt(mx**2 + my**2 + mz**2)
            mx *= recipNorm
            my *= recipNorm
            mz *= recipNorm

            # Auxiliary variables to avoid repeated arithmetic
            q0q0 = self.q0 * self.q0
            q0q1 = self.q0 * self.q1
            q0q2 = self.q0 * self.q2
            q0q3 = self.q0 * self.q3
            q1q1 = self.q1 * self.q1
            q1q2 = self.q1 * self.q2
            q1q3 = self.q1 * self.q3
            q2q2 = self.q2 * self.q2
            q2q3 = self.q2 * self.q3
            q3q3 = self.q3 * self.q3

            #   Reference direction of Earth's magnetic field
            hx = 2.0 * (mx * (0.5 - q2q2 - q3q3) + my * (q1q2 - q0q3) + mz * (q1q3 + q0q2))
            hy = 2.0 * (mx * (q1q2 + q0q3) + my * (0.5 - q1q1 - q3q3) + mz * (q2q3 - q0q1))
            bx = math.sqrt(hx * hx + hy * hy)
            bz = 2.0 * (mx * (q1q3 - q0q2) + my * (q2q3 + q0q1) + mz * (0.5 - q1q1 - q2q2))

            # Estimated direction of gravity and magnetic field
            halfvx = q1q3 - q0q2
            halfvy = q0q1 + q2q3
            halfvz = q0q0 - 0.5 + q3q3
            halfwx = bx * (0.5 - q2q2 - q3q3) + bz * (q1q3 - q0q2)
            halfwy = bx * (q1q2 - q0q3) + bz * (q0q1 + q2q3)
            halfwz = bx * (q0q2 + q1q3) + bz * (0.5 - q1q1 - q2q2)

            # Error is sum of cross product between estimated direction
            # and measured direction of field vector
            halfex = (ay * halfvz - az * halfvy) + (my * halfwz - mz * halfwy)
            halfey = (az * halfvx - ax * halfvz) + (mz * halfwx - mx * halfwz)
            halfez = (ax * halfvy - ay * halfvx) + (mx * halfwy - my * halfwx)


            if self.twoKi > 0:
                # integral error scaled by Ki
                integralFBx += self.twoKi * halfex * self.invSampleFreq
                integralFBy += self.twoKi * halfey * self.invSampleFreq
                integralFBz += self.twoKi * halfez * self.invSampleFreq
                gx += integralFBx;	# apply integral feedback
                gy += integralFBy
                gz += integralFBz

            else:
                integralFBx = 0.0	# prevent integral windup
                integralFBy = 0.0
                integralFBz = 0.0

            # Apply proportional feedback
            gx += self.twoKp * halfex
            gy += self.twoKp * halfey
            gz += self.twoKp * halfez
        
        
        # Integrate rate of change of quaternion
        gx *= (0.5 * self.invSampleFreq)		# pre-multiply common factors
        gy *= (0.5 * self.invSampleFreq)
        gz *= (0.5 * self.invSampleFreq)
        qa = self.q0
        qb = self.q1
        qc = self.q2
        self.q0 += (-qb * gx - qc * gy - self.q3 * gz)
        self.q1 += (qa * gx + qc * gz - self.q3 * gy)
        self.q2 += (qa * gy - qb * gz + self.q3 * gx)
        self.q3 += (qa * gz + qb * gy - qc * gx)  
   
        # Normalise quaternion
        recipNorm = 1/math.sqrt(self.q0**2 + self.q1**2 +self.q2**2 + self.q3**2)
        self.q0 *= recipNorm
        self.q1 *= recipNorm
        self.q2 *= recipNorm
        self.q3 *= recipNorm
        self.anglesComputed = True

        
    def updateIMU(self, gx, gy, gz, ax, ay, az):

        recipNorm = 0
        halfvx = halfvy = halfvz = 0
        halfex = halfey = halfez = 0
        qa = qb = qc = 0

        gx *= 0.0174533
        gy *= 0.0174533
        gz *= 0.0174533

        if (ax == 0.0) or (ay == 0.0) or (az == 0.0):
            # Normalise accelerometer measurement
            recipNorm = self.invSqrt(ax * ax + ay * ay + az * az)
            ax *= recipNorm
            ay *= recipNorm
            az *= recipNorm
            
            # Estimated direction of gravity
            halfvx = self.q1 * self.q3 - self.q0 * self.q2
            halfvy = self.q0 * self.q1 + self.q2 * self.q3
            halfvz = self.q0 * self.q0 - 0.5 + self.q3 * self.q3

            #Error is sum of cross product between estimated
            # and measured direction of gravity
            halfex = (ay * halfvz - az * halfvy)
            halfey = (az * halfvx - ax * halfvz)
            halfez = (ax * halfvy - ay * halfvx)

            # Compute and apply integral feedback if enabled
            if(self.twoKi > 0.0):
                # integral error scaled by Ki
                integralFBx += self.twoKi * halfex * self.invSampleFreq
                integralFBy += self.twoKi * halfey * self.invSampleFreq
                integralFBz += self.twoKi * halfez * self.invSampleFreq
                gx += integralFBx	# apply integral feedback
                gy += integralFBy
                gz += integralFBz
            else:
                integralFBx = 0.0 # prevent integral windup
                integralFBy = 0.0
                integralFBz = 0.0
            
            # Apply proportional feedback
            gx += self.twoKp * halfex
            gy += self.twoKp * halfey
            gz += self.twoKp * halfez
        
        gx *= (0.5 * self.invSampleFreq) # pre-multiply common factors
        gy *= (0.5 * self.invSampleFreq)
        gz *= (0.5 * self.invSampleFreq)
        qa = self.q0
        qb = self.q1
        qc = self.q2
        self.q0 += (-qb * gx - qc * gy - self.q3 * gz)
        self.q1 += (qa * gx + qc * gz - self.q3 * gy)
        self.q2 += (qa * gy - qb * gz + self.q3 * gx)
        self.q3 += (qa * gz + qb * gy - qc * gx)

        recipNorm = self.invSqrt(self.q0 * self.q0 + self.q1 * self.q1 + self.q2 * self.q2 + self.q3 * self.q3)
        self.q0 *= recipNorm
        self.q1 *= recipNorm
        self.q2 *= recipNorm
        self.q3 *= recipNorm
        self.anglesComputed = 0

            
            
    def invSqrt(self, x):
        threehalfs = 1.5
        x2 = x * 0.5
        y = np.float32(x)
        i = y.view(np.int32)
        i = np.int32(0x5f3759df) - np.int32(i >> 1)
        y = i.view(np.float32)
        y = y * (threehalfs - (x2 * y * y))
        return y


    def computeAngles(self):
        self.roll = math.atan2(self.q0*self.q1 + self.q2*self.q3, 0.5 - self.q1*self.q1 - self.q2*self.q2)
        self.pitch = math.asin(-2.0 * (self.q1*self.q3 - self.q0*self.q2))
        self.yaw = math.atan2(self.q1*self.q2 + self.q0*self.q3, 0.5 - self.q2*self.q2 - self.q3*self.q3)
        self.anglesComputed = 1
