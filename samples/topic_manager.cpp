void TopicManager::add_ros_topic(std::string ros_topic, bool telemetry_topic){
    // add ros topic and generate the corresponding mqtt topic
    std::stringstream ss;

    std::stringstream ros_topic_ss(ros_topic);
    std::string last_word;
    while(std::getline(ros_topic_ss, last_word, '/')){}

    ss << this->loader->get_mqtt_parameters("BASIC_TOPIC");
    ss << "/" << this->loader->get_mqtt_parameters("VEHICLE_TOPIC");
    ss << "/" << this->loader->get_mqtt_parameters("VEHICLE_ID");
    if(telemetry_topic){
        ss << "/" << this->loader->get_mqtt_parameters("VEHICLE_TELEMETRY_TOPIC");
    }
    ss << "/" << last_word;

    this->topic_list[ss.str()] = ros_topic;
}

void TopicManager::add_mqtt_topic(std::string mqtt_topic){
// add mqtt topic and generate the corresponding ros topic

    std::stringstream ss;

    std::stringstream ros_topic_ss(mqtt_topic);
    std::string last_word;
    while(std::getline(ros_topic_ss, last_word, '/')){}

    this->topic_list[mqtt_topic] = ss.str();
}

std::string TopicManager::get_ros_topic_from_mqtt(std::string mqtt_topic){
//get ros topic corresponding to the passed mqtt topic
    return this->topic_list[mqtt_topic];
}

std::string TopicManager::get_mqtt_topic_from_ros(std::string ros_topic){
//get mqtt topic corresponding to the passed ros topic
    std::string mqtt_topic;

    for (auto& it : this->topic_list) {
        if (it.second == ros_topic) {
            mqtt_topic = it.first;
        }
    }

    return mqtt_topic;
}
