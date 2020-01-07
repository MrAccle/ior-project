package com.ymh.iot.mapper;

import com.ymh.iot.pojo.Led;
import org.apache.ibatis.annotations.Param;
import org.apache.ibatis.annotations.ResultMap;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public interface LedMapper {
    int insert(Led record);

    int insertSelective(Led record);

    @Select("select * from led")
    @ResultMap("BaseResultMap")
    List<Led> getList();

    @Update("UPDATE `led` SET `state`=#{state} WHERE (`led`=#{led}) LIMIT 1")
    Integer changeLedState(@Param("led")String led,@Param("state")int state);
}