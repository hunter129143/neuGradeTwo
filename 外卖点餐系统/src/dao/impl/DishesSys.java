package dao.impl;



import dao.DAO;
import entity.Dishes;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.Set;

public class DishesSys implements DAO<Dishes> {
    // 建立一个菜品的map集合，其中菜品的id为map的键，整个菜品对象为map的值
     public static Map<String, Dishes> dishesmap = new HashMap<>();
    Set<String> keys = dishesmap.keySet();

    /**
     * 添加菜品
     */
    @Override
    public void insert(Dishes t) {
        dishesmap.put(t.getdID(), t);

    }

    /**
     * 通过id来寻找菜品
     */

    @Override
    public Dishes findById(String id) {
        if (dishesmap.get(id) == null) {
            return null;
        } else {
            return dishesmap.get(id);
        }
    }

    /**
     * 根据菜品类型查找菜品
     */
    public List<Dishes> findByType(String type) {
        List<Dishes> list = new ArrayList<>();
        for (String key : keys) {
            if (Objects.equals(type, dishesmap.get(key).getDtype())) {
                list.add(dishesmap.get(key));
            }

        }
        return list;
    }

    /**
     * 查询所有菜品
     */
    @Override
    public List<Dishes> findAll() {
        List<Dishes> list = new ArrayList<>();

        for (String str : keys) {
            list.add(dishesmap.get(str));
        }
        return list;
    }

    public void selectBytype(String typename) {
        int count = 0;
        for (String key : keys) {
            if (Objects.equals(dishesmap.get(key).getDtype(), typename)) {
                System.out.println(dishesmap.get(key));
                count++;
            }
        }
        if (count == 0) {
            System.out.println("没有当前类别的菜品！");
        }
    }

    /**
     * 删除指定id菜品
     */
    @Override
    public void delete(String id) {
        if (dishesmap.get(id) == null) {
            System.out.println("输入id错误...");
        } else {
            dishesmap.remove(id);
        }

    }

    @Override
    public void addMessage() {

    }
}