std::string ros_topic_to_mqtt_topic(std::string ros_topic){
  std::stringstream ss;

  std::stringstream ros_topic_ss(ros_topic);
  std::string last_word;
  while(std::getline(ros_topic_ss, last_word, '/')){}

  ss << loader->get_mqtt_parameters("BASIC_TOPIC");
  ss << "/" << loader->get_mqtt_parameters("VEHICLE_TOPIC");
  ss << "/" << loader->get_mqtt_parameters("VEHICLE_ID");
  ss << "/" << loader->get_mqtt_parameters("VEHICLE_TELEMETRY_TOPIC");
  ss << "/" << last_word;

  return ss.str();
}
