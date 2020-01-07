package com.ymh.iot.mapper;

import com.ymh.iot.pojo.Iotdevice;
import org.apache.ibatis.annotations.ResultMap;
import org.apache.ibatis.annotations.Select;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public interface IotdeviceMapper {
    int insert(Iotdevice record);

    int insertSelective(Iotdevice record);

    @Select("SELECT * FROM `iotdevice`")
    @ResultMap("BaseResultMap")
    List<Iotdevice> getDevice();
}