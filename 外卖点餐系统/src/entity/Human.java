package entity;

public class Human {
    private String ID;
    private String pwd;

    @Override
    public String toString() {
        return "Human{" +
                "ID='" + ID + '\'' +
                ", pwd='" + pwd + '\'' +
                '}';
    }

    public Human() {
    }

    public Human(String ID, String pwd) {
        this.ID = ID;
        this.pwd = pwd;
    }
    public String getID() {
        return ID;
    }
    public void setID(String ID) {
        this.ID = ID;
    }
    public String getpwd() {
        return pwd;
    }
    public void setpwd(String pwd) {
        this.pwd = pwd;
    }
}
