import numpy as np
import mxnet as mx



def pprint(info):
    print("[PTX] ", info)

class DebugOp(mx.operator.CustomOp):
    def forward(self, is_train, req, in_data, out_data, aux):
        data = in_data[1].asnumpy()
        pprint(data.shape)
        self.assign(out_data[0],req[0], in_data[0])

    def backward(self, req, out_grad, in_data, out_data, in_grad, aux):
        self.assign(in_grad[0],req[0], out_grad[0])


@mx.operator.register("debug")
class DebugProp(mx.operator.CustomOpProp):
    def __init__(self):
        super(DebugProp, self).__init__(True)

    def list_arguments(self):
        return ['input', 'debug']

    def list_outputs(self):
        return ['output']

    def infer_shape(self, in_shapes):
        """Calculate output shapes from input shapes. This can be
        omited if all your inputs and outputs have the same shape.

        in_shapes : list of shape. Shape is described by a tuple of int.
        """
        data_shape = in_shapes[0]
        debug_shape = in_shapes[1]

        output_shape = data_shape
        # return 3 lists representing inputs shapes, outputs shapes, and aux data shapes.
        return [data_shape, debug_shape] , (output_shape,), ()

    def create_operator(self, ctx, in_shapes, in_dtypes):
        #  create and return the CustomOp class.
        return DebugOp()