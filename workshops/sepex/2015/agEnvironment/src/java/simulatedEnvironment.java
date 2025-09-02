// Environment code for project agEnvironment

import jason.asSyntax.*;
import jason.environment.*;
import java.util.logging.*;

public class simulatedEnvironment extends Environment {

    private Logger logger = Logger.getLogger("agEnvironment."+simulatedEnvironment.class.getName());
    private int food = 100; 

    /** Called before the MAS execution with the args informed in .mas2j */
    @Override
    public void init(String[] args) {
        super.init(args);
        addPercept(Literal.parseLiteral("food(" + this.food + ")"));
    }

    @Override
    public boolean executeAction(String agName, Structure action) {
        if (action.getFunctor().equals("eat")) {
        	this.food -= 1;
        	clearPercepts();
        	addPercept(Literal.parseLiteral("food(" + this.food + ")"));
        	logger.info(agName + " ate 1 unit!");
        }
        return true;
    }

    /** Called before the end of MAS execution */
    @Override
    public void stop() {
        super.stop();
    }
}




