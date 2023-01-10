package entity;


public class Admin extends Human {

    private String account;




    @Override
    public String toString() {
        return "Admin{" +
                "ID='" + super.getID() + '\'' +
                ", account='" + account + '\'' +
                ", apwd='" + super.getpwd() + '\'' +
                '}';
    }

    public Admin() {
        // TODO Auto-generated constructor stub
    }
    public Admin(String ID, String account, String pwd) {
        super(ID,pwd);

        this.account = account;

    }

    public String getAccount() {
        return account;
    }
    public void setAccount(String account) {
        this.account = account;
    }


}