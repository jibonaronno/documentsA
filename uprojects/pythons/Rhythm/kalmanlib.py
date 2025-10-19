
import sys
import serial
import pprint
import time
import enum
import queue
from os.path import join, dirname, abspath
from qtpy.QtCore import Slot, QTimer, QThread, Signal, QObject, Qt, QMutex

class kalman(object):
    def __init__(self, time_step = 0.1):
        ##########################################################################
        # Model
        # Estimates
        self.estimate_position = 0.0
        self.estimate_velocity = 0.0

        # Covariance matrix
        self.P_xx = 0.01 # Variance of the position
        self.P_xv = 0.1 # Covariance of position and velocity
        self.P_vv = 0.1 # Variance of the velocity

        ##########################################################################
        # Model parameters
        self.position_process_variance = 0.01
        self.velocity_process_variance = 0.01
        self.R = 30.0 # Measurement noise variance

        self.average_length = 30
        self.data = []

        self.time_step = time_step
        self.sumofsteps = 0
        self.index = 0

    def Estimate(self, measurement):
        
        if self.index == 0:
            self.estimate_position = measurement       
        elif self.index == 1: # Second measurement
            self.estimate_velocity = ( measurement - self.estimate_position ) / self.time_step
            self.estimate_position = measurement
        else: # Can apply model
            ##################################################################
            # Temporal update (predictive)
            self.estimate_position += self.estimate_velocity * self.time_step
            self.P_xx += self.time_step * ( 2.0 * self.P_xv + self.time_step * self.P_vv )
            self.P_xv += self.time_step * self.P_vv
        
            self.P_xx += self.time_step * self.position_process_variance
            self.P_vv += self.time_step * self.velocity_process_variance
        
            ##################################################################       
            # Observational update (reactive)
            vi = 1.0 / ( self.P_xx + self.R )
            kx = self.P_xx * vi
            kv = self.P_xv * vi

            self.estimate_position += (measurement - self.estimate_position) * kx
            self.estimate_velocity += (measurement - self.estimate_position) * kv

            self.P_xx *= ( 1 - kx )
            self.P_xv *= ( 1 - kx )
            self.P_vv -= kv * self.P_xv
        
        self.index += 1
        return self.estimate_position