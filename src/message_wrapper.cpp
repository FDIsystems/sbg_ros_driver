#include "message_wrapper.h"

using sbg::MessageWrapper;

/*!
 * Class to wrap the SBG logs into ROS messages.
 */
//---------------------------------------------------------------------//
//- Constructor                                                       -//
//---------------------------------------------------------------------//

MessageWrapper::MessageWrapper(void)
{

}

//---------------------------------------------------------------------//
//- Internal methods                                                  -//
//---------------------------------------------------------------------//

const ros::Time MessageWrapper::createRosTime(uint32 device_timestamp) const
{
  //
  // Temporary.
  // TODO. Improve Ros time with the UTC/GPS time and device timestamp.
  //
  return ros::Time::now();
}

const geometry_msgs::Vector3 MessageWrapper::createRosVector3(const float* p_float_array) const
{
  geometry_msgs::Vector3 vector3_message;

  vector3_message.x = p_float_array[0];
  vector3_message.y = p_float_array[1];
  vector3_message.z = p_float_array[2];

  return vector3_message;
}

const geometry_msgs::Vector3 MessageWrapper::createRosVector3(const double* p_double_array) const
{
  geometry_msgs::Vector3 vector3_message;

  vector3_message.x = p_double_array[0];
  vector3_message.y = p_double_array[1];
  vector3_message.z = p_double_array[2];

  return vector3_message;
}

const sbg_driver::SbgEkfStatus MessageWrapper::createEkfStatusMessage(uint32 ekf_status) const
{
  sbg_driver::SbgEkfStatus ekf_status_message;

  ekf_status_message.solution_mode    = sbgEComLogEkfGetSolutionMode(ekf_status);
  ekf_status_message.attitude_valid   = ekf_status & SBG_ECOM_SOL_ATTITUDE_VALID;
  ekf_status_message.heading_valid    = ekf_status & SBG_ECOM_SOL_HEADING_VALID;
  ekf_status_message.velocity_valid   = ekf_status & SBG_ECOM_SOL_VELOCITY_VALID;
  ekf_status_message.position_valid   = ekf_status & SBG_ECOM_SOL_POSITION_VALID;

  ekf_status_message.vert_ref_used    = ekf_status & SBG_ECOM_SOL_VERT_REF_USED;
  ekf_status_message.mag_ref_used     = ekf_status & SBG_ECOM_SOL_MAG_REF_USED;
  ekf_status_message.gps1_vel_used    = ekf_status & SBG_ECOM_SOL_GPS1_VEL_USED;
  ekf_status_message.gps1_pos_used    = ekf_status & SBG_ECOM_SOL_GPS1_POS_USED;
  ekf_status_message.gps1_course_used = ekf_status & SBG_ECOM_SOL_GPS1_HDT_USED;
  ekf_status_message.gps1_hdt_used    = ekf_status & SBG_ECOM_SOL_GPS1_HDT_USED;
  ekf_status_message.gps2_vel_used    = ekf_status & SBG_ECOM_SOL_GPS2_VEL_USED;
  ekf_status_message.gps2_pos_used    = ekf_status & SBG_ECOM_SOL_GPS2_POS_USED;
  ekf_status_message.gps2_course_used = ekf_status & SBG_ECOM_SOL_GPS2_POS_USED;
  ekf_status_message.gps2_hdt_used    = ekf_status & SBG_ECOM_SOL_GPS2_HDT_USED;
  ekf_status_message.odo_used         = ekf_status & SBG_ECOM_SOL_ODO_USED;

  return ekf_status_message;
}

const sbg_driver::SbgGpsPosStatus MessageWrapper::createGpsPosStatusMessage(const SbgLogGpsPos& ref_log_gps_pos) const
{
  sbg_driver::SbgGpsPosStatus gps_pos_status_message;

  gps_pos_status_message.status       = sbgEComLogGpsPosGetStatus(ref_log_gps_pos.status);
  gps_pos_status_message.type         = sbgEComLogGpsPosGetType(ref_log_gps_pos.status);
  gps_pos_status_message.gps_l1_used  = ref_log_gps_pos.status & SBG_ECOM_GPS_POS_GPS_L1_USED;
  gps_pos_status_message.gps_l2_used  = ref_log_gps_pos.status & SBG_ECOM_GPS_POS_GPS_L2_USED;
  gps_pos_status_message.gps_l5_used  = ref_log_gps_pos.status & SBG_ECOM_GPS_POS_GPS_L5_USED;
  gps_pos_status_message.glo_l1_used  = ref_log_gps_pos.status & SBG_ECOM_GPS_POS_GLO_L1_USED;
  gps_pos_status_message.glo_l2_used  = ref_log_gps_pos.status & SBG_ECOM_GPS_POS_GLO_L2_USED;

  return gps_pos_status_message;
}

const sbg_driver::SbgGpsVelStatus MessageWrapper::createGpsVelStatusMessage(const SbgLogGpsVel& ref_log_gps_vel) const
{
  sbg_driver::SbgGpsVelStatus gps_vel_status_message;

  gps_vel_status_message.vel_status = sbgEComLogGpsVelGetStatus(ref_log_gps_vel.status);
  gps_vel_status_message.vel_type   = sbgEComLogGpsVelGetType(ref_log_gps_vel.status);

  return gps_vel_status_message;
}

const sbg_driver::SbgImuStatus MessageWrapper::createImuStatusMessage(const SbgLogImuData& ref_log_imu) const
{
  sbg_driver::SbgImuStatus imu_status_message;

  imu_status_message.imu_com              = ref_log_imu.status & SBG_ECOM_IMU_COM_OK;
  imu_status_message.imu_status           = ref_log_imu.status & SBG_ECOM_IMU_STATUS_BIT;
  imu_status_message.imu_accel_x          = ref_log_imu.status & SBG_ECOM_IMU_ACCEL_X_BIT;
  imu_status_message.imu_accel_y          = ref_log_imu.status & SBG_ECOM_IMU_ACCEL_Y_BIT;
  imu_status_message.imu_accel_z          = ref_log_imu.status & SBG_ECOM_IMU_ACCEL_Z_BIT;
  imu_status_message.imu_gyro_x           = ref_log_imu.status & SBG_ECOM_IMU_GYRO_X_BIT;
  imu_status_message.imu_gyro_y           = ref_log_imu.status & SBG_ECOM_IMU_GYRO_Y_BIT;
  imu_status_message.imu_gyro_z           = ref_log_imu.status & SBG_ECOM_IMU_GYRO_Z_BIT;
  imu_status_message.imu_accels_in_range  = ref_log_imu.status & SBG_ECOM_IMU_ACCELS_IN_RANGE;
  imu_status_message.imu_gyros_in_range   = ref_log_imu.status & SBG_ECOM_IMU_GYROS_IN_RANGE;

  return imu_status_message;
}

const sbg_driver::SbgMagStatus MessageWrapper::createMagStatusMessage(const SbgLogMag& ref_log_mag) const
{
  sbg_driver::SbgMagStatus mag_status_message;

  mag_status_message.mag_x            = ref_log_mag.status & SBG_ECOM_MAG_MAG_X_BIT;
  mag_status_message.mag_y            = ref_log_mag.status & SBG_ECOM_MAG_MAG_Y_BIT;
  mag_status_message.mag_z            = ref_log_mag.status & SBG_ECOM_MAG_MAG_Z_BIT;
  mag_status_message.accel_x          = ref_log_mag.status & SBG_ECOM_MAG_ACCEL_X_BIT;
  mag_status_message.accel_y          = ref_log_mag.status & SBG_ECOM_MAG_ACCEL_Y_BIT;
  mag_status_message.accel_z          = ref_log_mag.status & SBG_ECOM_MAG_ACCEL_Z_BIT;
  mag_status_message.mags_in_range    = ref_log_mag.status & SBG_ECOM_MAG_MAGS_IN_RANGE;
  mag_status_message.accels_in_range  = ref_log_mag.status & SBG_ECOM_MAG_ACCELS_IN_RANGE;
  mag_status_message.calibration      = ref_log_mag.status & SBG_ECOM_MAG_CALIBRATION_OK;

  return mag_status_message;
}

const sbg_driver::SbgShipMotionStatus MessageWrapper::createShipMotionStatusMessage(const SbgLogShipMotionData& ref_log_ship_motion) const
{
  sbg_driver::SbgShipMotionStatus ship_motion_status_message;

  ship_motion_status_message.heave_valid      = ref_log_ship_motion.status & SBG_ECOM_HEAVE_VALID;
  ship_motion_status_message.heave_vel_aided  = ref_log_ship_motion.status & SBG_ECOM_HEAVE_VEL_AIDED;
  ship_motion_status_message.period_available = ref_log_ship_motion.status & SBG_ECOM_HEAVE_PERIOD_INCLUDED;
  ship_motion_status_message.period_valid     = ref_log_ship_motion.status & SBG_ECOM_HEAVE_PERIOD_VALID;

  return ship_motion_status_message;
}

const sbg_driver::SbgStatusAiding MessageWrapper::createStatusAidingMessage(const SbgLogStatusData& ref_log_status) const
{
  sbg_driver::SbgStatusAiding status_aiding_message;

  status_aiding_message.gps1_pos_recv = ref_log_status.aidingStatus & SBG_ECOM_AIDING_GPS1_POS_RECV;
  status_aiding_message.gps1_vel_recv = ref_log_status.aidingStatus & SBG_ECOM_AIDING_GPS1_VEL_RECV;
  status_aiding_message.gps1_hdt_recv = ref_log_status.aidingStatus & SBG_ECOM_AIDING_GPS1_HDT_RECV;
  status_aiding_message.gps1_utc_recv = ref_log_status.aidingStatus & SBG_ECOM_AIDING_GPS1_UTC_RECV;

  status_aiding_message.mag_recv = ref_log_status.aidingStatus & SBG_ECOM_AIDING_MAG_RECV;
  status_aiding_message.odo_recv = ref_log_status.aidingStatus & SBG_ECOM_AIDING_ODO_RECV;
  status_aiding_message.dvl_recv = ref_log_status.aidingStatus & SBG_ECOM_AIDING_DVL_RECV;

  return status_aiding_message;
}

const sbg_driver::SbgStatusCom MessageWrapper::createStatusComMessage(const SbgLogStatusData& ref_log_status) const
{
  sbg_driver::SbgStatusCom status_com_message;

  status_com_message.port_a = ref_log_status.comStatus & SBG_ECOM_PORTA_VALID;
  status_com_message.port_b = ref_log_status.comStatus & SBG_ECOM_PORTB_VALID;
  status_com_message.port_c = ref_log_status.comStatus & SBG_ECOM_PORTC_VALID;
  status_com_message.port_d = ref_log_status.comStatus & SBG_ECOM_PORTD_VALID;
  status_com_message.port_e = ref_log_status.comStatus & SBG_ECOM_PORTE_VALID;

  status_com_message.port_a_rx = ref_log_status.comStatus & SBG_ECOM_PORTA_RX_OK;
  status_com_message.port_a_tx = ref_log_status.comStatus & SBG_ECOM_PORTA_TX_OK;
  status_com_message.port_b_rx = ref_log_status.comStatus & SBG_ECOM_PORTB_RX_OK;
  status_com_message.port_b_tx = ref_log_status.comStatus & SBG_ECOM_PORTB_TX_OK;
  status_com_message.port_c_rx = ref_log_status.comStatus & SBG_ECOM_PORTC_RX_OK;
  status_com_message.port_c_tx = ref_log_status.comStatus & SBG_ECOM_PORTC_TX_OK;
  status_com_message.port_d_rx = ref_log_status.comStatus & SBG_ECOM_PORTD_RX_OK;
  status_com_message.port_d_tx = ref_log_status.comStatus & SBG_ECOM_PORTD_TX_OK;
  status_com_message.port_e_rx = ref_log_status.comStatus & SBG_ECOM_PORTE_RX_OK;
  status_com_message.port_e_tx = ref_log_status.comStatus & SBG_ECOM_PORTE_TX_OK;

  status_com_message.can_rx     = ref_log_status.comStatus & SBG_ECOM_CAN_RX_OK;
  status_com_message.can_tx     = ref_log_status.comStatus & SBG_ECOM_CAN_TX_OK;
  status_com_message.can_status = ref_log_status.comStatus & SBG_ECOM_CAN_VALID;

  return status_com_message;
}

const sbg_driver::SbgStatusGeneral MessageWrapper::createStatusGeneralMessage(const SbgLogStatusData& ref_log_status) const
{
  sbg_driver::SbgStatusGeneral status_general_message;

  status_general_message.main_power   = ref_log_status.generalStatus & SBG_ECOM_GENERAL_MAIN_POWER_OK;
  status_general_message.imu_power    = ref_log_status.generalStatus & SBG_ECOM_GENERAL_IMU_POWER_OK;
  status_general_message.gps_power    = ref_log_status.generalStatus & SBG_ECOM_GENERAL_GPS_POWER_OK;
  status_general_message.settings     = ref_log_status.generalStatus & SBG_ECOM_GENERAL_SETTINGS_OK;
  status_general_message.temperature  = ref_log_status.generalStatus & SBG_ECOM_GENERAL_TEMPERATURE_OK;

  return status_general_message;
}

const sbg_driver::SbgUtcTimeStatus MessageWrapper::createUtcStatusMessage(const SbgLogUtcData& ref_log_utc) const
{
  sbg_driver::SbgUtcTimeStatus utc_status_message;

  utc_status_message.clock_stable     = ref_log_utc.status & SBG_ECOM_CLOCK_STABLE_INPUT;
  utc_status_message.clock_status     = ref_log_utc.status & SBG_ECOM_CLOCK_STATUS_MASK;
  utc_status_message.clock_utc_sync   = ref_log_utc.status & SBG_ECOM_CLOCK_UTC_SYNC;
  utc_status_message.clock_utc_status = ref_log_utc.status & SBG_ECOM_CLOCK_UTC_STATUS_SHIFT;
  
  return utc_status_message;
}

//---------------------------------------------------------------------//
//- Operations                                                        -//
//---------------------------------------------------------------------//

const sbg_driver::SbgEkfEuler MessageWrapper::createSbgEkfEulerMessage(const SbgLogEkfEulerData& ref_log_ekf_euler) const
{
  sbg_driver::SbgEkfEuler ekf_euler_message;

  ekf_euler_message.header.stamp  = createRosTime(ref_log_ekf_euler.timeStamp);
  ekf_euler_message.time_stamp    = ref_log_ekf_euler.timeStamp;

  ekf_euler_message.status    = createEkfStatusMessage(ref_log_ekf_euler.status);
  ekf_euler_message.angle     = createRosVector3(ref_log_ekf_euler.euler);
  ekf_euler_message.accuracy  = createRosVector3(ref_log_ekf_euler.eulerStdDev);

  return ekf_euler_message;
}

const sbg_driver::SbgEkfNav MessageWrapper::createSbgEkfNavMessage(const SbgLogEkfNavData& ref_log_ekf_nav) const
{
  sbg_driver::SbgEkfNav ekf_nav_message;

  ekf_nav_message.header.stamp  = createRosTime(ref_log_ekf_nav.timeStamp);
  ekf_nav_message.time_stamp    = ekf_nav_message.time_stamp;

  ekf_nav_message.status            = createEkfStatusMessage(ref_log_ekf_nav.status);
  ekf_nav_message.velocity          = createRosVector3(ref_log_ekf_nav.velocity);
  ekf_nav_message.velocity_accuracy = createRosVector3(ref_log_ekf_nav.velocityStdDev);
  ekf_nav_message.position          = createRosVector3(ref_log_ekf_nav.position);
  ekf_nav_message.undulation        = ref_log_ekf_nav.undulation;

  return ekf_nav_message;
}

const sbg_driver::SbgEkfQuat MessageWrapper::createSbgEkfQuatMessage(const SbgLogEkfQuatData& ref_log_ekf_quat) const
{
  sbg_driver::SbgEkfQuat ekf_quat_message;

  ekf_quat_message.header.stamp = createRosTime(ref_log_ekf_quat.timeStamp);
  ekf_quat_message.time_stamp   = ref_log_ekf_quat.timeStamp;

  ekf_quat_message.status       = createEkfStatusMessage(ref_log_ekf_quat.status);
  ekf_quat_message.quaternion.x = ref_log_ekf_quat.quaternion[1];
  ekf_quat_message.quaternion.y = ref_log_ekf_quat.quaternion[2];
  ekf_quat_message.quaternion.z = ref_log_ekf_quat.quaternion[3];
  ekf_quat_message.quaternion.w = ref_log_ekf_quat.quaternion[0];
  ekf_quat_message.accuracy     = createRosVector3(ref_log_ekf_quat.eulerStdDev);

  return ekf_quat_message;
}

const sbg_driver::SbgEvent MessageWrapper::createSbgEventMessage(const SbgLogEvent& ref_log_event) const
{
  sbg_driver::SbgEvent event_message;

  event_message.header.stamp  = createRosTime(ref_log_event.timeStamp);
  event_message.time_stamp    = ref_log_event.timeStamp;

  event_message.overflow        = ref_log_event.status & SBG_ECOM_EVENT_OVERFLOW;
  event_message.offset_0_valid  = ref_log_event.status & SBG_ECOM_EVENT_OFFSET_0_VALID;
  event_message.offset_1_valid  = ref_log_event.status & SBG_ECOM_EVENT_OFFSET_1_VALID;
  event_message.offset_2_valid  = ref_log_event.status & SBG_ECOM_EVENT_OFFSET_2_VALID;
  event_message.offset_3_valid  = ref_log_event.status & SBG_ECOM_EVENT_OFFSET_3_VALID;

  event_message.time_offset_0   = ref_log_event.timeOffset0;
  event_message.time_offset_1   = ref_log_event.timeOffset1;
  event_message.time_offset_2   = ref_log_event.timeOffset2;
  event_message.time_offset_3   = ref_log_event.timeOffset3;

  return event_message;
}

const sbg_driver::SbgGpsHdt MessageWrapper::createSbgGpsHdtMessage(const SbgLogGpsHdt& ref_log_gps_hdt) const
{
  sbg_driver::SbgGpsHdt gps_hdt_message;

  gps_hdt_message.header.stamp  = createRosTime(ref_log_gps_hdt.timeStamp);
  gps_hdt_message.time_stamp    = ref_log_gps_hdt.timeStamp;

  gps_hdt_message.status            = ref_log_gps_hdt.status;
  gps_hdt_message.tow               = ref_log_gps_hdt.timeOfWeek;
  gps_hdt_message.true_heading      = ref_log_gps_hdt.heading;
  gps_hdt_message.true_heading_acc  = ref_log_gps_hdt.headingAccuracy;
  gps_hdt_message.pitch             = ref_log_gps_hdt.pitch;
  gps_hdt_message.pitch_acc         = ref_log_gps_hdt.pitchAccuracy;

  return gps_hdt_message; 
}

const sbg_driver::SbgGpsPos MessageWrapper::createSbgGpsPosMessage(const SbgLogGpsPos& ref_log_gps_pos) const
{
  sbg_driver::SbgGpsPos gps_pos_message;

  gps_pos_message.header.stamp  = createRosTime(ref_log_gps_pos.timeStamp);
  gps_pos_message.time_stamp    = ref_log_gps_pos.timeStamp;

  gps_pos_message.status              = createGpsPosStatusMessage(ref_log_gps_pos);
  gps_pos_message.gps_tow             = ref_log_gps_pos.timeOfWeek;
  gps_pos_message.position.x          = ref_log_gps_pos.latitude;
  gps_pos_message.position.y          = ref_log_gps_pos.longitude;
  gps_pos_message.position.z          = ref_log_gps_pos.altitude;
  gps_pos_message.undulation          = ref_log_gps_pos.undulation;
  gps_pos_message.position_accuracy.x = ref_log_gps_pos.latitudeAccuracy;
  gps_pos_message.position_accuracy.y = ref_log_gps_pos.longitudeAccuracy;
  gps_pos_message.position_accuracy.z = ref_log_gps_pos.altitudeAccuracy;
  gps_pos_message.num_sv_used         = ref_log_gps_pos.numSvUsed;
  gps_pos_message.base_station_id     = ref_log_gps_pos.baseStationId;
  gps_pos_message.diff_age            = ref_log_gps_pos.differentialAge;

  return gps_pos_message;
}

const sbg_driver::SbgGpsRaw MessageWrapper::createSbgGpsRawMessage(const SbgLogGpsRaw& ref_log_gps_raw) const
{
  sbg_driver::SbgGpsRaw gps_raw_message;

  gps_raw_message.data.assign(ref_log_gps_raw.rawBuffer, ref_log_gps_raw.rawBuffer + ref_log_gps_raw.bufferSize);

  return gps_raw_message;
}

const sbg_driver::SbgGpsVel MessageWrapper::createSbgGpsVelMessage(const SbgLogGpsVel& ref_log_gps_vel) const
{
  sbg_driver::SbgGpsVel gps_vel_message;

  gps_vel_message.header.stamp  = createRosTime(ref_log_gps_vel.timeStamp);
  gps_vel_message.time_stamp    = ref_log_gps_vel.timeStamp;

  gps_vel_message.status      = createGpsVelStatusMessage(ref_log_gps_vel);
  gps_vel_message.gps_tow     = ref_log_gps_vel.timeOfWeek;
  gps_vel_message.vel         = createRosVector3(ref_log_gps_vel.velocity);
  gps_vel_message.vel_acc     = createRosVector3(ref_log_gps_vel.velocityAcc);
  gps_vel_message.course      = ref_log_gps_vel.course;
  gps_vel_message.course_acc  = ref_log_gps_vel.courseAcc;

  return gps_vel_message;
}

const sbg_driver::SbgImuData MessageWrapper::createSbgImuDataMessage(const SbgLogImuData& ref_log_imu_data) const
{
  sbg_driver::SbgImuData imu_data_message;

  imu_data_message.header.stamp = createRosTime(ref_log_imu_data.timeStamp);
  imu_data_message.time_stamp   = ref_log_imu_data.timeStamp;

  imu_data_message.imu_status   = createImuStatusMessage(ref_log_imu_data);
  imu_data_message.accel        = createRosVector3(ref_log_imu_data.accelerometers);
  imu_data_message.gyro         = createRosVector3(ref_log_imu_data.gyroscopes);
  imu_data_message.temp         = ref_log_imu_data.temperature;
  imu_data_message.delta_vel    = createRosVector3(ref_log_imu_data.deltaVelocity);
  imu_data_message.delta_angle  = createRosVector3(ref_log_imu_data.deltaAngle);

  return imu_data_message;
}

const sbg_driver::SbgMag MessageWrapper::createSbgMagMessage(const SbgLogMag& ref_log_mag) const
{
  sbg_driver::SbgMag mag_message;

  mag_message.header.stamp  = createRosTime(ref_log_mag.timeStamp);
  mag_message.time_stamp    = ref_log_mag.timeStamp;

  mag_message.mag     = createRosVector3(ref_log_mag.magnetometers);
  mag_message.accel   = createRosVector3(ref_log_mag.accelerometers);
  mag_message.status  = createMagStatusMessage(ref_log_mag);

  return mag_message;
}

const sbg_driver::SbgMagCalib MessageWrapper::createSbgMagCalibMessage(const SbgLogMagCalib& ref_log_mag_calib) const
{
  sbg_driver::SbgMagCalib mag_calib_message;

  // TODO. SbgMagCalib is not implemented.
  mag_calib_message.header.stamp = createRosTime(ref_log_mag_calib.timeStamp);

  return mag_calib_message;
}

const sbg_driver::SbgOdoVel MessageWrapper::createSbgOdoVelMessage(const SbgLogOdometerData& ref_log_odo) const
{
  sbg_driver::SbgOdoVel odo_vel_message;

  odo_vel_message.header.stamp  = createRosTime(ref_log_odo.timeStamp);
  odo_vel_message.time_stamp    = ref_log_odo.timeStamp;

  odo_vel_message.status  = ref_log_odo.status;
  odo_vel_message.vel     = ref_log_odo.velocity;

  return odo_vel_message;
}

const sbg_driver::SbgPressure MessageWrapper::createSbgPressureMessage(const SbgLogPressureData& ref_log_pressure) const
{
  sbg_driver::SbgPressure pressure_message;

  pressure_message.header.stamp = createRosTime(ref_log_pressure.timeStamp);
  pressure_message.time_stamp   = ref_log_pressure.timeStamp;

  pressure_message.valid_pressure = ref_log_pressure.status & SBG_ECOM_PRESSURE_PRESSURE_VALID;
  pressure_message.valid_altitude = ref_log_pressure.status & SBG_ECOM_PRESSURE_HEIGHT_VALID;
  pressure_message.pressure       = ref_log_pressure.pressure;
  pressure_message.altitude       = ref_log_pressure.height;

  return pressure_message;
}

const sbg_driver::SbgShipMotion MessageWrapper::createSbgShipMotionMessage(const SbgLogShipMotionData& ref_log_ship_motion) const
{
  sbg_driver::SbgShipMotion ship_motion_message;

  ship_motion_message.header.stamp  = createRosTime(ref_log_ship_motion.timeStamp);
  ship_motion_message.time_stamp    = ref_log_ship_motion.timeStamp;

  ship_motion_message.ship_motion   = createRosVector3(ref_log_ship_motion.shipMotion);
  ship_motion_message.acceleration  = createRosVector3(ref_log_ship_motion.shipAccel);
  ship_motion_message.velocity      = createRosVector3(ref_log_ship_motion.shipVel);
  ship_motion_message.status        = createShipMotionStatusMessage(ref_log_ship_motion);

  return ship_motion_message;
}

const sbg_driver::SbgStatus MessageWrapper::createSbgStatusMessage(const SbgLogStatusData& ref_log_status) const
{
  sbg_driver::SbgStatus status_message;

  status_message.header.stamp = createRosTime(ref_log_status.timeStamp);
  status_message.time_stamp   = ref_log_status.timeStamp;

  status_message.status_general = createStatusGeneralMessage(ref_log_status);
  status_message.status_com     = createStatusComMessage(ref_log_status);
  status_message.status_aiding  = createStatusAidingMessage(ref_log_status);

  return status_message;
}

const sbg_driver::SbgUtcTime MessageWrapper::createSbgUtcTimeMessage(const SbgLogUtcData& ref_log_utc) const
{
  sbg_driver::SbgUtcTime utc_time_message;

  utc_time_message.header.stamp = createRosTime(ref_log_utc.timeStamp);
  utc_time_message.time_stamp   = ref_log_utc.timeStamp;

  utc_time_message.clock_status = createUtcStatusMessage(ref_log_utc);
  utc_time_message.year         = ref_log_utc.year;
  utc_time_message.month        = ref_log_utc.month;
  utc_time_message.day          = ref_log_utc.day;
  utc_time_message.hour         = ref_log_utc.hour;
  utc_time_message.min          = ref_log_utc.minute;
  utc_time_message.sec          = ref_log_utc.second;
  utc_time_message.nanosec      = ref_log_utc.nanoSecond;
  utc_time_message.gps_tow      = ref_log_utc.gpsTimeOfWeek;

  return utc_time_message;
}