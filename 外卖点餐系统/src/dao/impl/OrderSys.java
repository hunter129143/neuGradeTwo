package dao.impl;

import dao.DAO;
import entity.Order;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

public class OrderSys implements DAO<Order> {
    public static Map<String, Order> ordermap = new HashMap<>();
    static List<Order> orderlist = new ArrayList<>();
    /**
     * 新增订单
     */
    @Override
    public void insert(Order t) {
        ordermap.put(t.getOrderID(), t);

    }
    /**
     * 通过订单id查找订单
     */
    @Override
    public Order findById(String id) {
        if (ordermap.get(id) == null) {
            return null;
        } else {
            return ordermap.get(id);
        }

    }
    /**
     * 通过用户id查询用户的所有订单，并返回一个list集合
     * @param uid
     * @return
     */
    public List<Order> findByuId(String uid) {
        List<Order> list = new ArrayList<>();
        Set<String> keys = ordermap.keySet();
        for (String key : keys) {
            if (Objects.equals(uid, ordermap.get(key).getuID())) {
                list.add(ordermap.get(key));
            }
        }
        return list;
    }

    /**
     * 显示所有订单
     */
    @Override
    public List<Order> findAll() {
        Set<String> keys = ordermap.keySet();
        for (String key : keys) {
            orderlist.add(ordermap.get(key));
        }
        return orderlist;
    }
    /**
     * 删除订单
     */
    @Override
    public void delete(String id) {
        // TODO Auto-generated method stub
        if (ordermap.get(id) == null) {
            System.out.println("输入id错误...");
        } else {
            ordermap.remove(id);
        }
    }

    @Override
    public void addMessage() {

    }
}