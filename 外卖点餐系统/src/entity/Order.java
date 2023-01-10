package entity;

import java.time.LocalDateTime;

public class Order {
    private String OrderID;
    private LocalDateTime utime;
    private Dishes dishes;
    private int Ordernum;
    private String uID;
    private Double Orderprice;
    private int OrderValue;

    public Order() {
        // TODO Auto-generated constructor stub
    }

    public Order(String orderID, LocalDateTime utime, Dishes dishes, int ordernum, String uID, Double orderprice,
                 int orderValue) {
        super();
        OrderID = orderID;
        this.utime = utime;
        this.dishes = dishes;
        Ordernum = ordernum;
        this.uID = uID;
        Orderprice = orderprice;
        OrderValue = orderValue;
    }

    public String getOrderID() {
        return OrderID;
    }

    public void setOrderID(String orderID) {
        OrderID = orderID;
    }

    public LocalDateTime getUtime() {
        return utime;
    }

    public void setUtime(LocalDateTime utime) {
        this.utime = utime;
    }

    public Double getOrderprice() {
        return Orderprice;
    }

    public void setOrderprice(Double orderprice) {
        Orderprice = orderprice;
    }

    public Dishes getDishes() {
        return dishes;
    }

    public void setDishes(Dishes dishes) {
        this.dishes = dishes;
    }

    public int getOrdernum() {
        return Ordernum;
    }

    public void setOrdernum(int ordernum) {
        Ordernum = ordernum;
    }

    public String getuID() {
        return uID;
    }

    public void setuID(String uID) {
        this.uID = uID;
    }

    public int getOrderValue() {
        return OrderValue;
    }

    public void setOrderValue(int orderValue) {
        OrderValue = orderValue;
    }

    @Override
    public String toString() {
        return "Order [OrderID=" + OrderID + ", utime=" + utime + ", dishes=" + dishes + ", Ordernum=" + Ordernum
                + ", uID=" + uID + ", Orderprice=" + Orderprice + ", OrderValue=" + OrderValue + "]";
    }

}