MsgsCache::MsgsCache(int history_length){
    this->history_length = history_length;
}

void MsgsCache::addTopic(std::string topic){
    topicList.push_back(topic);
}

void MsgsCache::setTopicList(std::vector<std::string> topic_list){
    this->topicList = topic_list;
}

std::vector<std::string> MsgsCache::getTopics(){
    return topicList;
}

void MsgsCache::addMsg(std::string topic, std::string message){
    this->mutex.lock();  
    if(std::count(this->topicList.begin(), this->topicList.end(), topic)<1)
        this->topicList.push_back(topic);
    
    if(this->cache[topic].size() >= this->history_length){
      this->cache[topic].pop_front();
    }
    this->cache[topic].push_back(message);
    this->mutex.unlock();  
}

std::string MsgsCache::getLastMsg(std::string topic){
    std::string return_value("");
    if(this->cache[topic].size() > 0){
      return_value = this->cache[topic].front();  
    }
    return return_value;
}

std::string MsgsCache::popLastMsg(std::string topic){
    this->mutex.lock();  

    std::string msg = this->getLastMsg(topic);
    if(this->cache[topic].size() > 1){
        this->cache[topic].pop_front();
    }
  
    this->mutex.unlock();  

    return msg;
}
int MsgsCache::getCacheSize(std::string topic){
  return this->cache[topic].size();
}      

