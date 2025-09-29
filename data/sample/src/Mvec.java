import java.lang.ref.Cleaner;
import java.lang.foreign.MemorySegment;
import org.garamon.project_namespace.Mvec_h;

public final class Mvec implements AutoCloseable {
    private static final Cleaner CLEANER = Cleaner.create();

    private static final class Native implements Runnable {
        MemorySegment seg;

        Native(MemorySegment s) {
            this.seg = s;
        }

        @Override
        public void run() {
            if (seg != null)
                Mvec_h.Mvec_delete(seg);
        }
    }

    private final Native nativeState;
    private final Cleaner.Cleanable cleanable;

    private Mvec(MemorySegment seg) {
        this.nativeState = new Native(seg);
        this.cleanable = CLEANER.register(this, nativeState);
    }

    public static Mvec empty() {
        return new Mvec(Mvec_h.Mvec_new_empty());
    }

    public static Mvec scalar(double v) {
        return new Mvec(Mvec_h.Mvec_new_scalar(v));
    }

project_static_multivector_one_component

    public static Mvec I() {
        return new Mvec(Mvec_h.Mvec_I());
    }

    private MemorySegment seg() {
        return nativeState.seg;
    }

    // ops "value-like"
    public Mvec add(Mvec b) {
        return new Mvec(Mvec_h.Mvec_add(seg(), b.seg()));
    }

    public Mvec add(double s) {
        return new Mvec(Mvec_h.Mvec_add_scalar(seg(), s));
    }

    // public Mvec radd(double s) {
    // return new Mvec(Mvec_h.Mvec_scalar_add(s, seg()));
    // }

    public Mvec mul(Mvec b) {
        return new Mvec(Mvec_h.Mvec_mul(seg(), b.seg()));
    }

    public Mvec mul(double s) {
        return new Mvec(Mvec_h.Mvec_mul_scalar(seg(), s));
    }

    public Mvec rmul(double s) {
        return new Mvec(Mvec_h.Mvec_scalar_mul(s, seg()));
    }

    public Mvec outer(Mvec b) {
        return new Mvec(Mvec_h.Mvec_outer(seg(), b.seg()));
    }

    public Mvec inner(Mvec b) {
        return new Mvec(Mvec_h.Mvec_inner(seg(), b.seg()));
    }

    public Mvec leftContraction(Mvec b) {
        return new Mvec(Mvec_h.Mvec_left_contraction(seg(), b.seg()));
    }

    public Mvec rightContraction(Mvec b) {
        return new Mvec(Mvec_h.Mvec_right_contraction(seg(), b.seg()));
    }

    public double norm() {
        return Mvec_h.Mvec_norm(seg());
    }

    public int highestGrade() {
        return Mvec_h.Mvec_get_highest_grade(seg());
    }

    public double toScalar() {
        return Mvec_h.Mvec_to_scalar(seg());
    }

    public void setCoeff(int i, double v) {
        Mvec_h.Mvec_set_coeff(seg(), i, v);
    }

    public double getCoeff(int i) {
        return Mvec_h.Mvec_get_coeff(seg(), i);
    }

    public void display() {
        Mvec_h.Mvec_display(seg());
    }

    public boolean isEmpty() {
        return Mvec_h.Mvec_is_empty(seg());
    }

    public void clear() {
        Mvec_h.Mvec_clear(seg(), -1);
    }

    @Override
    public void close() {
        cleanable.clean();
    }

    // public static final int SCALAR = 0, E1 = 1, E2 = 2, E12 = 3;
}
